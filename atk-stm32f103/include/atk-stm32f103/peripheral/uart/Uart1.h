#pragma once
#include<atk-stm32f103/peripheral/dma/Uart1TxDmaChannel.h>
#include<hal-wrapper/peripheral/uart/Uart.h>

extern "C"
{
	void USART1_IRQHandler();
}

namespace atk
{
	/// <summary>
	///		发送引脚 PA9，接收引脚 PA10。
	/// </summary>
	class Uart1 :public hal::Uart
	{
	private:
		friend void ::USART1_IRQHandler();
		Uart1() = default;
		Uart1 &operator=(Uart1 const &value) = delete;

		uint8_t _receive_buffer[1]{};
		uint16_t _receive_buffer_size = 1;

		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;

	protected:
		hal::UartCallbackFunc MspInitCallback() override;
		hal::UartCallbackFunc ReceiveCompleteCallback() override;

	public:
		USART_TypeDef *HardwareInstance() override;

		static Uart1 &Instance()
		{
			static Uart1 instance;
			return instance;
		}

		uint8_t *ReceiveBuffer() override;
		uint16_t ReceiveBufferSize() override;

		hal::DmaChannel &TxDmaChannel() override
		{
			return Uart1TxDmaChannel::Instance();
		}
	};
}
