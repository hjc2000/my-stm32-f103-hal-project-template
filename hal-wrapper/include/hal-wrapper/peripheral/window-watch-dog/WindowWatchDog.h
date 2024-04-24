#pragma once
#include<hal-wrapper/interrupt/Interrupt.h>
#include<hal-wrapper/peripheral/window-watch-dog/IWindowWatchDog.h>

namespace hal
{
	class WindowWatchDog :public IWindowWatchDog
	{
		WWDG_HandleTypeDef _handle;

	public:
		WWDG_HandleTypeDef *Handle() override;
		WWDG_TypeDef *HardwareInstance() override;

		WindowWatchDogInitCallbackFunc MspInitCallbackFunc() override;
		WindowWatchDogInitCallbackFunc EarlyWakeUpInterruptCallbackFunc() override;

		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;

		static WindowWatchDog &Instance()
		{
			static WindowWatchDog o;
			return o;
		}
	};
}

extern "C"
{
	void WWDG_IRQHandler();
}
