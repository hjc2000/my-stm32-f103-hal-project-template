#pragma once
#include<functional>
#include<hal-wrapper/IClockSwitchable.h>
#include<hal-wrapper/IHandleWrapper.h>
#include<hal-wrapper/IHardwareInstanceWrapper.h>
#include<hal-wrapper/interrupt/Interrupt.h>
#include<hal-wrapper/peripheral/window-watch-dog/WindowWatchDogInitOptions.h>

namespace hal
{
	using WindowWatchDogInitCallbackFunc = void(*)(WWDG_HandleTypeDef *handle);

	class WindowWatchDog :
		public hal::IHandleWrapper<WWDG_HandleTypeDef>,
		public hal::IHardwareInstanceWrapper<WWDG_TypeDef>,
		public hal::IClockSwitchable
	{
		WWDG_HandleTypeDef _handle;
		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;

	public:
		WWDG_HandleTypeDef *Handle() override;
		WWDG_TypeDef *HardwareInstance() override;

		WindowWatchDogInitCallbackFunc MspInitCallbackFunc();
		WindowWatchDogInitCallbackFunc EarlyWakeUpInterruptCallbackFunc();

		void Initialize(WindowWatchDogInitOptions const &options);

		void Feed()
		{
			HAL_WWDG_Refresh(Handle());
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

extern "C"
{
	/// <summary>
	///		中断向量函数
	/// </summary>
	void WWDG_IRQHandler();
}
