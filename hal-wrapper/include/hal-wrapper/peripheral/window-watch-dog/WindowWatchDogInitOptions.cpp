#include"WindowWatchDogInitOptions.h"

hal::WindowWatchDogInitOptions::WindowWatchDogInitOptions(WWDG_InitTypeDef const &o)
{
	*this = o;
}

hal::WindowWatchDogInitOptions &hal::WindowWatchDogInitOptions::operator=(WWDG_InitTypeDef const &o)
{
	_prescaler = (WindowWatchDogPrescaler)o.Prescaler;
	_window_upper_bound = o.Window;
	_counter_reload_value = o.Counter;
	_early_wakeup_interrupt_mode = (WindowWatchDogEarlyWakeupInterruptMode)o.EWIMode;
	return *this;
}

hal::WindowWatchDogInitOptions::operator WWDG_InitTypeDef()
{
	WWDG_InitTypeDef o;
	o.Prescaler = (uint32_t)_prescaler;
	o.Window = _window_upper_bound;
	o.Counter = _counter_reload_value;
	o.EWIMode = (uint32_t)_early_wakeup_interrupt_mode;
	return o;
}