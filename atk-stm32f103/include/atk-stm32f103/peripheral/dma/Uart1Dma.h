#pragma once
#include<hal-wrapper/peripheral/dma/DmaChannel.h>

namespace atk
{
	class Uart1Dma :public hal::DmaChannel
	{
	public:
		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;

	};
}