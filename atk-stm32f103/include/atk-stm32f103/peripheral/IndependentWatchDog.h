#pragma once
#include<hal-wrapper/peripheral/watch-dog/IIndependentWatchDog.h>

namespace atk
{
	class IndependentWatchDog :
		public hal::IIndependentWatchDog
	{
		IWDG_HandleTypeDef _handle;

	public:
		void Initialize(hal::WatchDogInitOptions const &options)
		{
			Handle()->Instance = HardwareInstance();
			Handle()->Init = options;
			HAL_IWDG_Init(Handle());
		}

		IWDG_HandleTypeDef *Handle() override
		{
			return &_handle;
		}

		IWDG_TypeDef *HardwareInstance() override
		{
			return IWDG;
		}
	};
}
