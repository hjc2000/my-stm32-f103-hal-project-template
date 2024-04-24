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
	return [](WWDG_HandleTypeDef *handle)->void
	{
		WindowWatchDog::Instance().EnableClock();
		Interrupt::SetPriority(IRQn_Type::WWDG_IRQn, 2, 3);
		Interrupt::EnableIRQ(IRQn_Type::WWDG_IRQn);
	};
}

WindowWatchDogInitCallbackFunc hal::WindowWatchDog::EarlyWakeUpInterruptCallbackFunc()
{
	return [](WWDG_HandleTypeDef *handle)->void
	{
		WindowWatchDog::Instance().Feed();
	};
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

void WWDG_IRQHandler()
{
	HAL_WWDG_IRQHandler(WindowWatchDog::Instance().Handle());
}
