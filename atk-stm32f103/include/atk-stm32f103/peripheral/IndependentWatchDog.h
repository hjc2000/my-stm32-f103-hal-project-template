#pragma once
#include<hal-wrapper/peripheral/watch-dog/IIndependentWatchDog.h>

namespace atk
{
	class IndependentWatchDog :
		public hal::IIndependentWatchDog
	{
		IWDG_HandleTypeDef _handle;

	public:
		IWDG_HandleTypeDef *Handle() override
		{
			return &_handle;
		}

		IWDG_TypeDef *HardwareInstance() override
		{
			return IWDG;
		}

		uint32_t InnerClockSourceFreq_Hz() override
		{
			// 独立看门狗具有 40 kHz 的内部时钟。
			return 40 * 1000;
		}
	};
}
