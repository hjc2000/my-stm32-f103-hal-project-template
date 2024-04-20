#pragma once
#include<hal-wrapper/peripheral/Uart.h>

namespace atk
{
	#ifdef USART1
	class Uart1 :public hal::Uart
	{
		uint8_t _receive_buffer[1]{};
		uint16_t _receive_buffer_size = 1;

	public:
		// 通过 Uart 继承
		bool IsClockEnabled() override;

		void EnableClock() override;

		void DisableClock() override;

		hal::UartCallbackFunc MspInitCallback() override;

		hal::UartCallbackFunc ReceiveCompleteCallback() override;

		USART_TypeDef *HardwareInstance() override;

		uint8_t *ReceiveBuffer() override;

		uint16_t ReceiveBufferSize() override;

	};
	#endif // USART0
}