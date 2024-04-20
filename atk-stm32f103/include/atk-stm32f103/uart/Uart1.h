#pragma once
#include<hal-wrapper/peripheral/GpioPort.h>
#include<hal-wrapper/peripheral/Uart.h>

namespace atk
{
	/// <summary>
	///		发送引脚 PA9，接收引脚 PA10。
	/// </summary>
	class Uart1 :public hal::Uart
	{
		Uart1() = default;
		Uart1 &operator=(Uart1 const &value) = delete;

		uint8_t _receive_buffer[1]{};
		uint16_t _receive_buffer_size = 1;

		static void MspInit(UART_HandleTypeDef *huart);

	public:
		static Uart1 &Instance()
		{
			static Uart1 instance;
			return instance;
		}

		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;

		hal::UartCallbackFunc MspInitCallback() override;
		hal::UartCallbackFunc ReceiveCompleteCallback() override;

		USART_TypeDef *HardwareInstance() override;

		uint8_t *ReceiveBuffer() override;
		uint16_t ReceiveBufferSize() override;

	};
}