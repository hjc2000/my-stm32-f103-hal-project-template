#pragma once
#include<hal-wrapper/IClockSwitchable.h>
#include<hal-wrapper/IHandleWrapper.h>
#include<hal-wrapper/IHardwareInstanceWrapper.h>
#include<hal-wrapper/peripheral/window-watch-dog/WindowWatchDogInitOptions.h>

namespace hal
{
	using WindowWatchDogInitCallbackFunc = void(*)(WWDG_HandleTypeDef *handle);

	/// <summary>
	///		窗口看门狗接口
	/// </summary>
	class IWindowWatchDog :
		public hal::IHandleWrapper<WWDG_HandleTypeDef>,
		public hal::IHardwareInstanceWrapper<WWDG_TypeDef>,
		public hal::IClockSwitchable
	{
	public:
		virtual WindowWatchDogInitCallbackFunc MspInitCallbackFunc() = 0;
		virtual WindowWatchDogInitCallbackFunc EarlyWakeUpInterruptCallbackFunc() = 0;

		void Initialize(WindowWatchDogInitOptions const &options)
		{
			Handle()->Instance = HardwareInstance();
			Handle()->Init = options;
			Handle()->MspInitCallback = MspInitCallbackFunc();
			Handle()->EwiCallback = EarlyWakeUpInterruptCallbackFunc();
			HAL_WWDG_Init(Handle());
		}
	};
}
