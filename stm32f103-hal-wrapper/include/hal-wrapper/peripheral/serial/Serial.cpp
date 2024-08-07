#include "Serial.h"
#include <FreeRTOS.h>
#include <base/Initializer.h>
#include <bsp-interface/di.h>
#include <hal-wrapper/interrupt/Interrupt.h>
#include <hal-wrapper/peripheral/dma/DmaConfig.h>
#include <task.h>

using namespace hal;
using namespace bsp;

static base::Initializer _init{
	[]()
	{
		hal::Serial::Instance();
	}};

void Serial::OnMspInitCallback(UART_HandleTypeDef *huart)
{
	__HAL_RCC_USART1_CLK_ENABLE();

	auto init_gpio = []()
	{
		// PA9
		{
			auto options = DICreate_GpioPinOptions();
			options->SetAlternateFunction("af_push_pull");
			options->SetDirection(bsp::IGpioPinDirection::Output);
			options->SetDriver(bsp::IGpioPinDriver::PushPull);
			options->SetPullMode(bsp::IGpioPinPullMode::PullUp);
			options->SetSpeedLevel(2);
			options->SetWorkMode(bsp::IGpioPinWorkMode::AlternateFunction);
			bsp::IGpioPin *pin = DI_GpioPinCollection().Get("PA9");
			pin->Open(*options);
		}

		// PA10
		{
			auto options = DICreate_GpioPinOptions();
			options->SetAlternateFunction("af_input");
			options->SetDirection(bsp::IGpioPinDirection::Input);
			options->SetPullMode(bsp::IGpioPinPullMode::PullUp);
			options->SetSpeedLevel(2);
			options->SetWorkMode(bsp::IGpioPinWorkMode::AlternateFunction);
			bsp::IGpioPin *pin = DI_GpioPinCollection().Get("PA10");
			pin->Open(*options);
		}
	};

	auto init_tx_dma = []()
	{
		__HAL_RCC_DMA1_CLK_ENABLE();
		hal::DmaConfig dma_config{};
		dma_config._data_transfer_direction = hal::DmaConfig::DataTransferDirection::MemoryToPeripheral;
		dma_config._peripheral_inc_mode = hal::DmaConfig::PeripheralIncMode::Disable;
		dma_config._mem_inc_mode = hal::DmaConfig::MemoryIncMode::Enable;
		dma_config._peripheral_data_alignment = hal::DmaConfig::PeripheralDataAlignment::Byte;
		dma_config._mem_data_alignment = hal::DmaConfig::MemoryDataAlignment::Byte;
		dma_config._mode = hal::DmaConfig::Mode::Normal;
		dma_config._priority = hal::DmaConfig::Priority::Medium;

		Serial::Instance()._tx_dma_handle.Instance = DMA1_Channel4;
		Serial::Instance()._tx_dma_handle.Init = dma_config;
		HAL_DMA_Init(&Serial::Instance()._tx_dma_handle);
	};

	auto init_rx_dma = []()
	{
		__HAL_RCC_DMA1_CLK_ENABLE();
		hal::DmaConfig dma_config{};
		dma_config._data_transfer_direction = hal::DmaConfig::DataTransferDirection::PeripheralToMemory;
		dma_config._peripheral_inc_mode = hal::DmaConfig::PeripheralIncMode::Disable;
		dma_config._mem_inc_mode = hal::DmaConfig::MemoryIncMode::Enable;
		dma_config._peripheral_data_alignment = hal::DmaConfig::PeripheralDataAlignment::Byte;
		dma_config._mem_data_alignment = hal::DmaConfig::MemoryDataAlignment::Byte;
		dma_config._mode = hal::DmaConfig::Mode::Normal;
		dma_config._priority = hal::DmaConfig::Priority::Medium;

		Serial::Instance()._rx_dma_handle.Instance = DMA1_Channel5;
		Serial::Instance()._rx_dma_handle.Init = dma_config;
		HAL_DMA_Init(&Serial::Instance()._rx_dma_handle);
	};

	// 连接到 DMA 发送通道
	auto link_dma_channel = []()
	{
		Serial::Instance()._uart_handle.hdmatx = &Serial::Instance()._tx_dma_handle;
		Serial::Instance()._tx_dma_handle.Parent = &Serial::Instance()._uart_handle;

		Serial::Instance()._uart_handle.hdmarx = &Serial::Instance()._rx_dma_handle;
		Serial::Instance()._rx_dma_handle.Parent = &Serial::Instance()._uart_handle;
	};

	init_gpio();
	init_tx_dma();
	init_rx_dma();
	link_dma_channel();
}

#pragma region 被中断处理函数回调的函数
void Serial::OnReceiveEventCallback(UART_HandleTypeDef *huart, uint16_t pos)
{
	Serial::Instance()._current_receive_count = pos;
	Serial::Instance()._receive_complete_signal.ReleaseFromISR();
}

void Serial::OnSendCompleteCallback(UART_HandleTypeDef *huart)
{
	Serial::Instance()._send_complete_signal.ReleaseFromISR();
}
#pragma endregion

void Serial::Open(bsp::ISerialOptions const &options)
{
	/*
	 * 先立刻释放一次信号量，等会 Write 方法被调用时直接通过，不被阻塞。
	 * 然后在发送完成之前，第二次 Write 就会被阻塞了，这还能防止 Write
	 * 被多线程同时调用。
	 */
	_send_complete_signal.Release();
	_uart_handle.Instance = USART1;
	_uart_handle.Init = static_cast<SerialOptions const &>(options);
	_uart_handle.MspInitCallback = OnMspInitCallback;
	HAL_UART_Init(&_uart_handle);

	/*
	 * HAL_UART_Init 函数会把中断处理函数中回调的函数都设为默认的，所以必须在 HAL_UART_Init
	 * 之后对函数指针赋值。
	 */
	_uart_handle.RxEventCallback = OnReceiveEventCallback;
	_uart_handle.TxCpltCallback = OnSendCompleteCallback;

	// 启用中断
	auto enable_interrupt = []()
	{
		hal::Interrupt::SetPriority(IRQn_Type::USART1_IRQn,
									10,
									0);
		DI_IsrManager().AddIsr(
			static_cast<uint32_t>(IRQn_Type::USART1_IRQn),
			[]()
			{
				HAL_UART_IRQHandler(&Serial::Instance()._uart_handle);
			});

		hal::Interrupt::SetPriority(IRQn_Type::DMA1_Channel4_IRQn,
									10,
									0);
		DI_IsrManager().AddIsr(
			static_cast<uint32_t>(IRQn_Type::DMA1_Channel4_IRQn),
			[]()
			{
				HAL_DMA_IRQHandler(&Serial::Instance()._tx_dma_handle);
			});

		hal::Interrupt::SetPriority(IRQn_Type::DMA1_Channel5_IRQn,
									10,
									0);
		DI_IsrManager().AddIsr(
			static_cast<uint32_t>(IRQn_Type::DMA1_Channel5_IRQn),
			[]()
			{
				HAL_DMA_IRQHandler(&Serial::Instance()._rx_dma_handle);
			});

		hal::Interrupt::EnableIRQ(IRQn_Type::USART1_IRQn);
		hal::Interrupt::EnableIRQ(IRQn_Type::DMA1_Channel4_IRQn);
		hal::Interrupt::EnableIRQ(IRQn_Type::DMA1_Channel5_IRQn);
	};

	enable_interrupt();
}

#pragma region Stream
int32_t Serial::Read(uint8_t *buffer, int32_t offset, int32_t count)
{
	if (count > UINT16_MAX)
	{
		throw std::invalid_argument{"count 太大"};
	}

	task::MutexLockGuard l{_read_lock};
	while (true)
	{
		task::Critical::Run(
			[&]()
			{
				HAL_UARTEx_ReceiveToIdle_DMA(&_uart_handle, buffer + offset, count);

				/*
				 * 通过赋值为空指针，把传输半满回调给禁用，不然接收的数据较长，超过缓冲区一半时，
				 * 即使是一次性接收的，UART 也会回调 OnReceiveEventCallback 两次。
				 *
				 * 这个操作需要在临界区中，并且 DMA 的中断要处于 freertos 的管理范围内，否则无效。
				 */
				_rx_dma_handle.XferHalfCpltCallback = nullptr;
			});

		_receive_complete_signal.Acquire();
		if (_current_receive_count > 0)
		{
			return _current_receive_count;
		}
	}
}

void Serial::Write(uint8_t const *buffer, int32_t offset, int32_t count)
{
	_send_complete_signal.Acquire();
	HAL_UART_Transmit_DMA(&_uart_handle, buffer + offset, count);
}

void Serial::Close()
{
	HAL_UART_DMAStop(&_uart_handle);
	hal::Interrupt::DisableIRQ(IRQn_Type::USART1_IRQn);
	hal::Interrupt::DisableIRQ(IRQn_Type::DMA1_Channel4_IRQn);
	hal::Interrupt::DisableIRQ(IRQn_Type::DMA1_Channel5_IRQn);
}
#pragma endregion
