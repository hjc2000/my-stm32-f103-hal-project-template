#include"WindowWatchDog.h"

using namespace hal;

WWDG_HandleTypeDef &WindowWatchDog::Handle()
{
	return _handle;
}

WWDG_TypeDef *WindowWatchDog::HardwareInstance()
{
	return WWDG;
}

WindowWatchDogInitCallbackFunc WindowWatchDog::MspInitCallbackFunc()
{
	return [](WWDG_HandleTypeDef *handle)->void
	{
		WindowWatchDog::Instance().EnableClock();
		Interrupt::SetPriority(IRQn_Type::WWDG_IRQn, 2, 3);
		Interrupt::EnableIRQ(IRQn_Type::WWDG_IRQn);
	};
}

WindowWatchDogInitCallbackFunc WindowWatchDog::EarlyWakeUpInterruptCallbackFunc()
{
	return [](WWDG_HandleTypeDef *handle)->void
	{
		WindowWatchDog::Instance().Feed();
		if (WindowWatchDog::Instance()._on_early_wakeup_interrupt)
		{
			WindowWatchDog::Instance()._on_early_wakeup_interrupt();
		}
	};
}

void WindowWatchDog::Initialize(WindowWatchDogConfig const &options)
{
	_handle.Instance = HardwareInstance();
	_handle.Init = _config.Handle();
	_handle.MspInitCallback = MspInitCallbackFunc();
	_handle.EwiCallback = EarlyWakeUpInterruptCallbackFunc();
	HAL_WWDG_Init(&_handle);
}

bool WindowWatchDog::IsClockEnabled()
{
	return __HAL_RCC_WWDG_IS_CLK_ENABLED();
}

void WindowWatchDog::EnableClock()
{
	__HAL_RCC_WWDG_CLK_ENABLE();
}

void WindowWatchDog::DisableClock()
{
	__HAL_RCC_WWDG_CLK_DISABLE();
}

extern "C"
{
	void WWDG_IRQHandler()
	{
		HAL_WWDG_IRQHandler(&WindowWatchDog::Instance().Handle());
	}
}
