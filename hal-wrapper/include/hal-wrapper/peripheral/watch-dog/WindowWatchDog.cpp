#include"WindowWatchDog.h"

WWDG_HandleTypeDef *hal::WindowWatchDog::Handle()
{
	return &_handle;
}

WWDG_TypeDef *hal::WindowWatchDog::HardwareInstance()
{
	return WWDG;
}
