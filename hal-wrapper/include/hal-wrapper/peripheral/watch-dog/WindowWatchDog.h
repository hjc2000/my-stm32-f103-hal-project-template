#pragma once
#include<hal-wrapper/peripheral/watch-dog/IWindowWatchDog.h>

namespace hal
{
	class WindowWatchDog :public IWindowWatchDog
	{
		WWDG_HandleTypeDef _handle;

	public:
		WWDG_HandleTypeDef *Handle() override;
		WWDG_TypeDef *HardwareInstance() override;

	};
}
