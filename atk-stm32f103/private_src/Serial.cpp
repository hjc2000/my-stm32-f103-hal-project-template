#include"Serial.h"
#include<FreeRTOS.h>
#include<atk-stm32f103/bsp.h>
#include<hal-wrapper/interrupt/Interrupt.h>
#include<hal-wrapper/peripheral/dma/DmaInitOptions.h>
#include<hal-wrapper/peripheral/gpio/GpioPort.h>
#include<task.h>

using namespace hal;
using namespace atk;

void USART1_IRQHandler()
{
	HAL_UART_IRQHandler(&Serial::Instance()._uart_handle);
}

void DMA1_Channel4_IRQHandler()
{
	HAL_DMA_IRQHandler(&Serial::Instance()._dma_handle);
	BSP::GreenDigitalLed().Toggle();
}

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

	auto init_dma = []()
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

		Serial::Instance()._dma_handle.Instance = DMA1_Channel4;
		Serial::Instance()._dma_handle.Init = options;
		HAL_DMA_Init(&Serial::Instance()._dma_handle);
	};

	init_gpio();
	init_dma();

	// 连接到 DMA 发送通道
	Serial::Instance()._uart_handle.hdmatx = &Serial::Instance()._dma_handle;
	Serial::Instance()._dma_handle.Parent = Serial::Instance()._uart_handle.hdmatx;
}

void Serial::OnReceiveCompleteCallback(UART_HandleTypeDef *huart)
{
	// 退出中断处理函数前要再次调用一次，否则之后就无法中断，无法接收了。
	BSP::RedDigitalLed().Toggle();
	Serial::Instance().EnableReceiveInterrupt();
}

void atk::Serial::OnSendCompleteCallback(UART_HandleTypeDef *huart)
{
	//Serial::Instance()._send_complete_signal.ReleaseFromISR();
}

void Serial::EnableReceiveInterrupt()
{
	HAL_UART_Receive_IT(&_uart_handle, _receive_buffer, sizeof(_receive_buffer));
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
	SendWithDma(buffer + offset, count);
	//_send_complete_signal.Acquire();
	BSP::Delayer().Delay(std::chrono::seconds{ 1 });
	CloseDma();
}

void Serial::Flush()
{
	// Write 方法利用 DMA 直接发送缓冲区，本类没有内部缓冲区，不需要冲洗。
}

void Serial::Close()
{
	// 什么都不做。串口启用后没必要关闭。
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
	_baud_rate = baud_rate;
	UartInitOptions options;
	options._baud_rate = baud_rate;

	_uart_handle.Instance = _uart_hardware_instance;
	_uart_handle.Init = options;
	_uart_handle.MspInitCallback = OnMspInitCallback;

	// 启动
	HAL_UART_Init(&_uart_handle);
	_uart_handle.RxCpltCallback = OnReceiveCompleteCallback;
	_uart_handle.TxCpltCallback = OnSendCompleteCallback;
	_uart_handle.TxHalfCpltCallback = [](UART_HandleTypeDef *huart) {};
	_uart_handle.ErrorCallback = [](UART_HandleTypeDef *huart) {};

	// 启用中断
	Interrupt::SetPriority(IRQn_Type::USART1_IRQn, 10, 0);
	Interrupt::EnableIRQ(IRQn_Type::USART1_IRQn);
	Interrupt::SetPriority(IRQn_Type::DMA1_Channel4_IRQn, 10, 0);
	Interrupt::EnableIRQ(IRQn_Type::DMA1_Channel4_IRQn);
	EnableReceiveInterrupt();
}
