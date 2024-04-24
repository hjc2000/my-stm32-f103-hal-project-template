#include"Uart1.h"
#include<hal-wrapper/interrupt/Interrupt.h>
#include<hal-wrapper/peripheral/gpio/GpioPort.h>

using namespace hal;

void USART1_IRQHandler()
{
	HAL_UART_IRQHandler(Uart1::Instance().Handle());
}

bool Uart1::IsClockEnabled()
{
	return __HAL_RCC_USART1_IS_CLK_ENABLED();
}

void Uart1::EnableClock()
{
	__HAL_RCC_USART1_CLK_ENABLE();
}

void Uart1::DisableClock()
{
	__HAL_RCC_USART1_CLK_DISABLE();
}

hal::UartCallbackFunc Uart1::MspInitCallbackFunc()
{
	return [](UART_HandleTypeDef *huart)->void
	{
		GpioPortA::Instance().EnableClock();
		Uart1::Instance().EnableClock();

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
	};
}

hal::UartCallbackFunc Uart1::ReceiveCompleteInterruptCallbackFunc()
{
	return [](UART_HandleTypeDef *huart)->void
	{
		if (Uart1::Instance()._on_receive_completed_interrupt)
		{
			Uart1::Instance()._on_receive_completed_interrupt();
		}

		Uart1::Instance().EnableReceiveInterrupt();
	};
}

USART_TypeDef *Uart1::HardwareInstance()
{
	return USART1;
}

uint8_t *Uart1::ReceiveBuffer()
{
	return _receive_buffer;
}

uint16_t Uart1::ReceiveBufferSize()
{
	return _receive_buffer_size;
}

void Uart1::PerepareForNextDmaTx()
{
	Uart1TxDmaChannel::Instance().ClearTransferCompletedFlag();

	uint32_t dmarequest = 0x00U;
	/* The Lock is not implemented on this API to allow the user application
	to call the HAL UART API under callbacks HAL_UART_TxCpltCallback() / HAL_UART_RxCpltCallback():
	when calling HAL_DMA_Abort() API the DMA TX/RX Transfer complete interrupt is generated
	and the correspond call back is executed HAL_UART_TxCpltCallback() / HAL_UART_RxCpltCallback()
	*/

	/* Stop UART DMA Tx request if ongoing */
	dmarequest = HAL_IS_BIT_SET(Handle()->Instance->CR3, USART_CR3_DMAT);
	if ((Handle()->gState == HAL_UART_STATE_BUSY_TX) && dmarequest)
	{
		CLEAR_BIT(Handle()->Instance->CR3, USART_CR3_DMAT);

		/* Abort the UART DMA Tx channel */
		if (Handle()->hdmatx != NULL)
		{
			HAL_DMA_Abort(Handle()->hdmatx);
		}

		/* Disable TXEIE and TCIE interrupts */
		CLEAR_BIT(Handle()->Instance->CR1, (USART_CR1_TXEIE | USART_CR1_TCIE));

		/* At end of Tx process, restore Handle()->gState to Ready */
		Handle()->gState = HAL_UART_STATE_READY;
	}
}
