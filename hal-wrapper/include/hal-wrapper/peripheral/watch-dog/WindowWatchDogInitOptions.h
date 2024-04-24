#pragma once
#include<hal.h>

namespace hal
{
	enum class WindowWatchDogPrescaler
	{
		Div1 = WWDG_PRESCALER_1,
		Div2 = WWDG_PRESCALER_2,
		Div4 = WWDG_PRESCALER_4,
		Div8 = WWDG_PRESCALER_8,
	};

	enum class WindowWatchDogEarlyWakeupInterruptMode
	{
		Enable = WWDG_EWI_ENABLE,
		Disable = WWDG_EWI_DISABLE,
	};

	class WindowWatchDogInitOptions
	{
	public:
		WindowWatchDogPrescaler _prescaler;

		/// <summary>
		///		窗口上界，范围：[0x40, 0x7F]
		/// </summary>
		uint32_t _window;

		/// <summary>
		///		范围：[0x40, 0x7F]
		/// </summary>
		uint32_t Counter;

		WindowWatchDogEarlyWakeupInterruptMode _early_wakeup_interrupt_mode;
	};
}