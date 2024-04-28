#include"Serial.h"
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

void Serial::WaitForDmaTx()
{
	while (true)
	{
		if (Uart1TxDmaChannel::Instance().TransferCompleted())
		{
			return;
		}
	}
}

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
	// 发送采用一个缓冲区配合 DMA。DMA 没发送完就等待。
	SendWithDma(buffer + offset, count);
	WaitForDmaTx();
	PerepareForNextDmaTx();
}

void Serial::Flush()
{
	// 等待 DMA 发送完成

}

void Serial::Close()
{
	// 串口反初始化

}

int64_t Serial::Position()
{
	return 0;
}

void Serial::SetPosition(int64_t value)
{
}

void Serial::Begin(uint32_t baud_rate)
{
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

int32_t Serial::AvaliableToRead()
{
	// 返回循环缓冲区中的可用数据长度

	return 0;
}

int32_t Serial::AvaliableToWrite()
{
	/* 返回发送缓冲区剩余的长度。
	* 这里的缓冲区就是一个简单的数组，满了就调用 DMA 进行发送
	*/
	return 0;
}
