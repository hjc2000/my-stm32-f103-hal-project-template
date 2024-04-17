#pragma once
#include<hal-wrapper/peripheral/IPeripheral.h>

namespace hal
{
	class Usart :public IPeripheral
	{
	public:
		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;
	};
}