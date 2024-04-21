#pragma once

namespace hal
{
	class UartReceiveCompletedHandler
	{
	public:
		virtual void OnUartReceiveCompleted() = 0;
	};
}
