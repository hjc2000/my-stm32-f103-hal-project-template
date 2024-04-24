#pragma once
#include<hal-wrapper/IHandleWrapper.h>
#include<hal-wrapper/IHardwareInstanceWrapper.h>

namespace hal
{
	using WindowWatchDogInitCallbackFunc = void(*)(WWDG_HandleTypeDef *handle);

	class IWindowWatchDog :
		public hal::IHandleWrapper<WWDG_HandleTypeDef>,
		public hal::IHardwareInstanceWrapper<WWDG_TypeDef>
	{
	public:
		virtual WindowWatchDogInitCallbackFunc MspInitCallbackFunc() = 0;
		virtual WindowWatchDogInitCallbackFunc EarlyWakeUpInterruptCallbackFunc() = 0;
	};
}
