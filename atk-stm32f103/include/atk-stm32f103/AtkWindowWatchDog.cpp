#include"AtkWindowWatchDog.h"

WWDG_HandleTypeDef *atk::AtkWindowWatchDog::Handle()
{
	return nullptr;
}

WWDG_TypeDef *atk::AtkWindowWatchDog::HardwareInstance()
{
	return WWDG;
}
