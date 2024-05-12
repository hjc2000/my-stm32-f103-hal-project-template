#include"BaseTimerInitOptions.h"

using namespace hal;

hal::BaseTimerInitOptions::BaseTimerInitOptions(TIM_Base_InitTypeDef const &o)
{
	*this = o;
}

BaseTimerInitOptions &hal::BaseTimerInitOptions::operator=(TIM_Base_InitTypeDef const &o)
{
	_prescaler = o.Prescaler;
	_counter_mode = static_cast<CounterMode>(o.CounterMode);
	_period = o.Period;
	_clock_division = static_cast<ClockDivision>(o.ClockDivision);
	_repetition_counter = o.RepetitionCounter;
	_auto_reload_preload = static_cast<AutoReloadPreload>(o.AutoReloadPreload);
	return *this;
}

hal::BaseTimerInitOptions::operator TIM_Base_InitTypeDef()
{
	TIM_Base_InitTypeDef o;
	o.Prescaler = _prescaler;
	o.CounterMode = static_cast<uint32_t>(_counter_mode);
	o.Period = _period;
	o.ClockDivision = static_cast<uint32_t>(_clock_division);
	o.RepetitionCounter = _repetition_counter;
	o.AutoReloadPreload = static_cast<uint32_t>(_auto_reload_preload);
	return o;
}
