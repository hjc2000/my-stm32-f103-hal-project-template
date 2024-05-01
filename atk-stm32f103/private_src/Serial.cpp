#include"Serial.h"
#include<FreeRTOS.h>
#include<atk-stm32f103/bsp.h>
#include<hal-wrapper/interrupt/Interrupt.h>
#include<hal-wrapper/peripheral/dma/DmaInitOptions.h>
#include<hal-wrapper/peripheral/gpio/GpioPort.h>
#include<task.h>

using namespace hal;
using namespace atk;

#pragma region 中断处理函数
void USART1_IRQHandler()
{
	HAL_UART_IRQHandler(&Serial::Instance()._uart_handle);
}

void DMA1_Channel4_IRQHandler()
{
	HAL_DMA_IRQHandler(&Serial::Instance()._tx_dma_handle);
}

void DMA1_Channel5_IRQHandler()
{
	HAL_DMA_IRQHandler(&Serial::Instance()._rx_dma_handle);
}
#pragma endregion

void Serial::OnMspInitCallback(UART_HandleTypeDef *huart)
{
	auto init_gpio = []()
	{
		GpioPortA::Instance().EnableClock();
		__HAL_RCC_USART1_CLK_ENABLE();

		// 发送引脚 PA9
		GpioPinInitOptions options;
		options._mode = GpioPinMode::AlternateFunction_PushPull;
		options._pull_mode = GpioPinPull::PullUp;
		options._speed = GpioPinSpeed::High;
		GpioPortA::Instance().InitPin(GpioPin::Pin9, options);

		// 接收引脚 PA10
		options._mode = GpioPinMode::AlternateFunction_Input;
		GpioPortA::Instance().InitPin(GpioPin::Pin10, options);
	};

	auto init_tx_dma = []()
	{
		__HAL_RCC_DMA1_CLK_ENABLE();
		hal::DmaInitOptions options;
		options._direction = DmaDataTransferDirection::MemoryToPeripheral;
		options._peripheral_inc_mode = DmaPeripheralIncMode::Disable;
		options._mem_inc_mode = DmaMemoryIncMode::Enable;
		options._peripheral_data_alignment = PeripheralDataAlignment::Byte;
		options._mem_data_alignment = MemoryDataAlignment::Byte;
		options._mode = DmaMode::Normal;
		options._priority = DmaPriority::Medium;

		Serial::Instance()._tx_dma_handle.Instance = DMA1_Channel4;
		Serial::Instance()._tx_dma_handle.Init = options;
		HAL_DMA_Init(&Serial::Instance()._tx_dma_handle);
	};

	auto init_rx_dma = []()
	{
		__HAL_RCC_DMA1_CLK_ENABLE();
		hal::DmaInitOptions options;
		options._direction = DmaDataTransferDirection::PeripheralToMemory;
		options._peripheral_inc_mode = DmaPeripheralIncMode::Disable;
		options._mem_inc_mode = DmaMemoryIncMode::Enable;
		options._peripheral_data_alignment = PeripheralDataAlignment::Byte;
		options._mem_data_alignment = MemoryDataAlignment::Byte;
		options._mode = DmaMode::Normal;
		options._priority = DmaPriority::Medium;

		Serial::Instance()._rx_dma_handle.Instance = DMA1_Channel5;
		Serial::Instance()._rx_dma_handle.Init = options;
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
void atk::Serial::OnReceiveEventCallback(UART_HandleTypeDef *huart, uint16_t pos)
{
	static uint8_t count = 0;
	count++;
	Serial::Instance().WriteWithoutLock((uint8_t *)(&count), 0, 1);
	HAL_UARTEx_ReceiveToIdle_DMA(
		&Serial::Instance()._uart_handle,
		Serial::Instance()._receive_buffer,
		10
	);
}

void atk::Serial::OnSendCompleteCallback(UART_HandleTypeDef *huart)
{
	Serial::Instance()._send_complete_signal.ReleaseFromISR();
}
#pragma endregion

void atk::Serial::WriteWithoutLock(uint8_t const *buffer, int32_t offset, int32_t count)
{
	HAL_UART_Transmit_DMA(&_uart_handle, buffer + offset, count);
}

#pragma region Stream
bool Serial::CanRead()
{
	return true;
}

bool Serial::CanWrite()
{
	return true;
}

bool Serial::CanSeek()
{
	return false;
}

int64_t Serial::Length()
{
	return 0;
}

void Serial::SetLength(int64_t value)
{
	// 不支持的操作
}

int32_t Serial::Read(uint8_t *buffer, int32_t offset, int32_t count)
{
	// 接收采用循环缓冲区配合接收中断
	// 没有数据可读就一直等待，直到有数据可读。

	return 0;
}

void Serial::Write(uint8_t const *buffer, int32_t offset, int32_t count)
{
	_send_complete_signal.Acquire();
	HAL_UART_Transmit_DMA(&_uart_handle, buffer + offset, count);
}

void Serial::Flush()
{
	// Write 方法利用 DMA 直接发送缓冲区，本类没有内部缓冲区，不需要冲洗。
}

void Serial::Close()
{
	HAL_UART_DMAStop(&_uart_handle);
	Interrupt::DisableIRQ(IRQn_Type::USART1_IRQn);
	Interrupt::DisableIRQ(IRQn_Type::DMA1_Channel4_IRQn);
}

int64_t Serial::Position()
{
	return 0;
}

void Serial::SetPosition(int64_t value)
{
	// 不支持的操作。
}
#pragma endregion

void Serial::Begin(uint32_t baud_rate)
{
	/*
	* 先立刻释放一次信号量，等会 Write 方法被调用时直接通过，不被阻塞。
	* 然后在发送完成之前，第二次 Write 就会被阻塞了，这还能防止 Write
	* 被多线程同时调用。
	*/
	_send_complete_signal.Release();

	_baud_rate = baud_rate;
	UartInitOptions options;
	options._baud_rate = baud_rate;

	_uart_handle.Instance = _uart_hardware_instance;
	_uart_handle.Init = options;
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
		Interrupt::SetPriority(IRQn_Type::USART1_IRQn, 10, 0);
		Interrupt::EnableIRQ(IRQn_Type::USART1_IRQn);

		Interrupt::SetPriority(IRQn_Type::DMA1_Channel4_IRQn, 10, 0);
		Interrupt::EnableIRQ(IRQn_Type::DMA1_Channel4_IRQn);

		Interrupt::SetPriority(IRQn_Type::DMA1_Channel5_IRQn, 10, 0);
		Interrupt::EnableIRQ(IRQn_Type::DMA1_Channel5_IRQn);
	};

	enable_interrupt();

	// 启动接收
	HAL_UARTEx_ReceiveToIdle_DMA(&_uart_handle, _receive_buffer, 10);
}
