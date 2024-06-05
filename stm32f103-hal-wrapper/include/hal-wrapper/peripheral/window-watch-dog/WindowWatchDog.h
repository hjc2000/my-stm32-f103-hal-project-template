#pragma once
#include<functional>
#include<hal-wrapper/interrupt/Interrupt.h>
#include<hal-wrapper/peripheral/window-watch-dog/WindowWatchDogConfig.h>

namespace hal
{
	using WindowWatchDogInitCallbackFunc = void(*)(WWDG_HandleTypeDef *handle);

	class WindowWatchDog :public base::HandleWrapper<WWDG_HandleTypeDef>
	{
		WWDG_HandleTypeDef _handle;
		WindowWatchDogConfig _config;
		bool IsClockEnabled();
		void EnableClock();
		void DisableClock();

	public:
		WWDG_HandleTypeDef &Handle() override;
		WWDG_TypeDef *HardwareInstance();

		WindowWatchDogInitCallbackFunc MspInitCallbackFunc();
		WindowWatchDogInitCallbackFunc EarlyWakeUpInterruptCallbackFunc();

		void Initialize(WindowWatchDogConfig const &options);

		void Feed()
		{
			HAL_WWDG_Refresh(&_handle);
		}

		static WindowWatchDog &Instance()
		{
			static WindowWatchDog o;
			return o;
		}

		/// <summary>
		///		提早唤醒中断发生时触发的回调。
		///		* 不需要喂狗，因为本类的实现是先喂狗后再回调此函数的。
		/// </summary>
		std::function<void()> _on_early_wakeup_interrupt;
	};
}
