#pragma once

namespace hal
{
	using UartCallbackFunc = void (*)(UART_HandleTypeDef *huart);

	class UartReceiveCompletedHandler
	{
	public:
		virtual void OnUartReceiveCompleted() = 0;
	};
}
