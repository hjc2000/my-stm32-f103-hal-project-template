#pragma once
#include<functional>
#include<hal-wrapper/peripheral/dma/Uart1TxDmaChannel.h>
#include<hal-wrapper/peripheral/uart/IUart.h>

extern "C"
{
	void USART1_IRQHandler();
}

namespace hal
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
		///		接收完成时被回调。
		///		* 注意，这是在中断中被回调的，注意避免访问冲突。
		/// </summary>
		std::function<void()> _on_receive_completed_interrupt;

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

		void PerepareForNextDmaTx() override;
	};
}
