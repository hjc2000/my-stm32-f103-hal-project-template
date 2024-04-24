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

bool hal::WindowWatchDog::IsClockEnabled()
{
	return __HAL_RCC_WWDG_IS_CLK_ENABLED();
}

void hal::WindowWatchDog::EnableClock()
{
	__HAL_RCC_WWDG_CLK_ENABLE();
}

void hal::WindowWatchDog::DisableClock()
{
	__HAL_RCC_WWDG_CLK_DISABLE();
}
