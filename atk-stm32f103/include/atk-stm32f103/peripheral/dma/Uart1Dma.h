#pragma once
#include<hal-wrapper/peripheral/dma/Dma.h>

namespace atk
{
	class Uart1Dma :public hal::Dma
	{
	public:
		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;

	};
}