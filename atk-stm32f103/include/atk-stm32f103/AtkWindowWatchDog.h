#pragma once
#include<hal-wrapper/peripheral/watch-dog/IWindowWatchDog.h>

namespace atk
{
	class AtkWindowWatchDog :public hal::IWindowWatchDog
	{
	public:
		WWDG_HandleTypeDef *Handle() override;
		WWDG_TypeDef *HardwareInstance() override;

	};
}