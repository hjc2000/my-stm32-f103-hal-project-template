#pragma once
#include<atk-stm32f103/peripheral/dma/Uart1TxDmaChannel.h>
#include<hal-wrapper/peripheral/uart/IUart.h>

extern "C"
{
	void USART1_IRQHandler();
}

namespace atk
{
	/// <summary>
	///		发送引脚 PA9，接收引脚 PA10。
	/// </summary>
	class Uart1 :public hal::IUart
	{
	private:
		friend void ::USART1_IRQHandler();
		Uart1() = default;
		Uart1 &operator=(Uart1 const &value) = delete;

		UART_HandleTypeDef _handle;
		uint8_t _receive_buffer[1]{};
		uint16_t _receive_buffer_size = 1;

		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;

	protected:
		hal::UartCallbackFunc MspInitCallback() override;
		hal::UartCallbackFunc ReceiveCompleteCallback() override;

	public:
		/// <summary>
		///		接收完成时被回调
		/// </summary>
		void(*_on_receive_completed)() = nullptr;
		hal::UartReceiveCompletedHandler *_receive_completed_handler = nullptr;

		UART_HandleTypeDef *Handle() override
		{
			return &_handle;
		}

		USART_TypeDef *HardwareInstance() override;

		static Uart1 &Instance()
		{
			static Uart1 instance;
			return instance;
		}

		uint8_t *ReceiveBuffer() override;
		uint16_t ReceiveBufferSize() override;

		hal::IDmaChannel &TxDmaChannel() override
		{
			return Uart1TxDmaChannel::Instance();
		}

		void PerepareForNextDmaTx() override
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
	};
}
