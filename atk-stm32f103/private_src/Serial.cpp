#include"Serial.h"
#include<atk-stm32f103/bsp.h>
#include<hal-wrapper/interrupt/Interrupt.h>
#include<hal-wrapper/peripheral/dma/Uart1TxDmaChannel.h>
#include<hal-wrapper/peripheral/gpio/GpioPort.h>

using namespace hal;
using namespace atk;

void USART1_IRQHandler()
{
	HAL_UART_IRQHandler(&Serial::Instance()._handle);
}

void Serial::OnMspInitCallback(UART_HandleTypeDef *huart)
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

	// 启用中断
	Interrupt::SetPriority(IRQn_Type::USART1_IRQn, 3, 3);
	Interrupt::EnableIRQ(IRQn_Type::USART1_IRQn);
}

void Serial::OnReceiveCompleteCallback(UART_HandleTypeDef *huart)
{
	// 退出中断处理函数前要再次调用一次，否则之后就无法中断，无法接收了。
	BSP::RedDigitalLed().Toggle();
	Serial::Instance().EnableReceiveInterrupt();
}

void Serial::EnableReceiveInterrupt()
{
	HAL_UART_Receive_IT(&_handle, _receive_buffer, sizeof(_receive_buffer));
}

void Serial::WaitForDmaTx(int32_t data_size)
{
	/*
	* 当前正在发送的数据有 data_size 个字节，一个波特等于 1 个字节。
	* 于是，data_size 个字节共需要的发送时间为
	*	t = data_size / _baud_rate
	* 单位：秒。
	*
	* 于是至少需要等待
	*	ms = t * 1000
	* 单位：毫秒。
	*	ms = data_size / _baud_rate * 1000
	*	ms = data_size * 1000 / _baud_rate
	*/
	int64_t ms = data_size * 1000 / _baud_rate;
	if (ms > 0)
	{
		BSP::Delayer().Delay(std::chrono::milliseconds{ ms });
	}

	/* 等待了合理的时间后，一般是即将发送完成了，但也可能因为误差还没发送完，
	* 剩下的时间就轮询标志位，直到检测到发送成功。
	*/
	while (true)
	{
		if (Uart1TxDmaChannel::Instance().TransferCompleted())
		{
			// 轮询直到发送完成才返回
			return;
		}
	}
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
	WaitForDmaTx(count);
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

	_handle.Instance = _hardware_instance;
	_handle.Init = options;
	_handle.MspInitCallback = OnMspInitCallback;

	// 连接到 DMA 发送通道
	_handle.hdmatx = Uart1TxDmaChannel::Instance().Handle();
	Uart1TxDmaChannel::Instance().Handle()->Parent = _handle.hdmatx;

	// 启动
	HAL_UART_Init(&_handle);
	_handle.RxCpltCallback = OnReceiveCompleteCallback;
	EnableReceiveInterrupt();
}
