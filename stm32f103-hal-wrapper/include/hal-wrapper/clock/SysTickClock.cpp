#include "SysTickClock.h"
#include <hal-wrapper/clock/ClockSignal.h>

using namespace hal;

SysTickClock::SysTickClockSourceOption SysTickClock::ClockSource() const
{
	uint32_t masked = SysTick->CTRL & SysTick_CTRL_CLKSOURCE_Msk;
	if (masked)
	{
		return SysTickClockSourceOption::HCLK;
	}

	return SysTickClockSourceOption::HCLK_DIV8;
}

void SysTickClock::SetClockSource(SysTickClock::SysTickClockSourceOption value)
{
	HAL_SYSTICK_CLKSourceConfig(static_cast<uint32_t>(value));
}

uint32_t SysTickClock::Frequency() const
{
	if (ClockSource() == SysTickClockSourceOption::HCLK_DIV8)
	{
		// return hal::ClockSignal::HclkFreq() / 8;
	}

	return hal::ClockSignal::HclkFreq();
}

uint32_t SysTickClock::ReloadValue() const
{
	uint32_t masked = SysTick->LOAD & SysTick_LOAD_RELOAD_Msk;
	return masked >> SysTick_LOAD_RELOAD_Pos;
}

uint32_t SysTickClock::CurrentValue() const
{
	uint32_t masked = SysTick->VAL & SysTick_VAL_CURRENT_Msk;
	return masked >> SysTick_VAL_CURRENT_Pos;
}
