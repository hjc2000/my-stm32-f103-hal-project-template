#include"WindowWatchDog.h"

using namespace hal;

extern "C"
{
	void WWDG_IRQHandler()
	{
		HAL_WWDG_IRQHandler(&WindowWatchDog::Instance().Handle());
	}
}

void WindowWatchDog::OnMspInitCallback(WWDG_HandleTypeDef *handle)
{
	__HAL_RCC_WWDG_CLK_ENABLE();
	Interrupt::SetPriority(IRQn_Type::WWDG_IRQn, 4, 0);
	Interrupt::EnableIRQ(IRQn_Type::WWDG_IRQn);
}

void WindowWatchDog::OnEarlyWakeUpInterruptCallback(WWDG_HandleTypeDef *handle)
{
	WindowWatchDog::Instance().Feed();
	if (WindowWatchDog::Instance()._on_early_wakeup_interrupt)
	{
		WindowWatchDog::Instance()._on_early_wakeup_interrupt();
	}
}

WWDG_HandleTypeDef &WindowWatchDog::Handle()
{
	return _handle;
}

WWDG_TypeDef *WindowWatchDog::HardwareInstance()
{
	return WWDG;
}

void WindowWatchDog::Initialize(WindowWatchDogConfig &config)
{
	_handle.Instance = HardwareInstance();
	_handle.Init = config.Handle();
	_handle.MspInitCallback = OnMspInitCallback;
	_handle.EwiCallback = OnEarlyWakeUpInterruptCallback;
	HAL_WWDG_Init(&_handle);
}

void hal::WindowWatchDog::Feed()
{
	HAL_WWDG_Refresh(&_handle);
}
