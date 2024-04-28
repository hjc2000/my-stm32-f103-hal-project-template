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

void Serial::PerepareForNextDmaTx()
{
	Uart1TxDmaChannel::Instance().ClearTransferCompletedFlag();

	uint32_t dmarequest = 0x00U;
	/* The Lock is not implemented on this API to allow the user application
	to call the HAL UART API under callbacks HAL_UART_TxCpltCallback() / HAL_UART_RxCpltCallback():
	when calling HAL_DMA_Abort() API the DMA TX/RX Transfer complete interrupt is generated
	and the correspond call back is executed HAL_UART_TxCpltCallback() / HAL_UART_RxCpltCallback()
	*/

	/* Stop UART DMA Tx request if ongoing */
	dmarequest = HAL_IS_BIT_SET(_hardware_instance->CR3, USART_CR3_DMAT);
	if ((_handle.gState == HAL_UART_STATE_BUSY_TX) && dmarequest)
	{
		CLEAR_BIT(_hardware_instance->CR3, USART_CR3_DMAT);

		/* Abort the UART DMA Tx channel */
		if (_handle.hdmatx != NULL)
		{
			HAL_DMA_Abort(_handle.hdmatx);
		}

		/* Disable TXEIE and TCIE interrupts */
		CLEAR_BIT(_hardware_instance->CR1, (USART_CR1_TXEIE | USART_CR1_TCIE));

		/* At end of Tx process, restore Handle()->gState to Ready */
		_handle.gState = HAL_UART_STATE_READY;
	}
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
	*	ms = data_size / _baud_rate * 1000
	*	ms = data_size * 1000 / _baud_rate
	*/
	int64_t ms = data_size * 1000 / _baud_rate;
	if (ms > 0)
	{
		BSP::Delayer().Delay(std::chrono::milliseconds{ ms });
	}

	/* 等待了合理的时间后，一般是即将发送完成了，剩下的时间就轮询标志位，
	直到检测到发送成功。*/
	while (true)
	{
		if (Uart1TxDmaChannel::Instance().TransferCompleted())
		{
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
	PerepareForNextDmaTx();
}

void Serial::Flush()
{

}

void Serial::Close()
{

}

int64_t Serial::Position()
{
	return 0;
}

void Serial::SetPosition(int64_t value)
{

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
