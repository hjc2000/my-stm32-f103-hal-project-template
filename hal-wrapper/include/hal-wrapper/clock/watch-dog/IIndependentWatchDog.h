#pragma once
#include<hal-wrapper/IHandleWrapper.h>
#include<hal-wrapper/clock/watch-dog/WatchDogInitOptions.h>
#include<hal-wrapper/peripheral/IHardwareInstanceWrapper.h>

namespace hal
{
	/// <summary>
	///		独立看门狗。
	///		- 所谓独立看门狗就是具有自己的内部时钟源，不依赖单片机的系统时钟。
	///		  在系统时钟失效时仍然能工作。
	/// </summary>
	class IIndependentWatchDog :
		public IHandleWrapper<IWDG_HandleTypeDef>,
		public IHardwareInstanceWrapper<IWDG_TypeDef>
	{
	public:
		void Initialize(WatchDogInitOptions const &options)
		{
			Handle()->Instance = HardwareInstance();
			Handle()->Init = options;
			HAL_IWDG_Init(Handle());
		}

		void FeedDog()
		{
			HAL_IWDG_Refresh(Handle());
		}
	};
}