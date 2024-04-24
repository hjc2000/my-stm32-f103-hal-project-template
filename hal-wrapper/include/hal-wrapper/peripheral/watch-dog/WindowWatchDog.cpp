#include"WindowWatchDog.h"

using namespace hal;

WWDG_HandleTypeDef *hal::WindowWatchDog::Handle()
{
	return &_handle;
}

WWDG_TypeDef *hal::WindowWatchDog::HardwareInstance()
{
	return WWDG;
}

WindowWatchDogInitCallbackFunc hal::WindowWatchDog::MspInitCallbackFunc()
{
	return WindowWatchDogInitCallbackFunc();
}

WindowWatchDogInitCallbackFunc hal::WindowWatchDog::EarlyWakeUpInterruptCallbackFunc()
{
	return WindowWatchDogInitCallbackFunc();
}
