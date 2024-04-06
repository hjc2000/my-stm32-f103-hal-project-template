#include"SysticOperator.h"

SysticOperator g_systic_operator{};

bool SysticOperator::CountFlag()
{
	uint32_t masked = SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk;
	return masked >> SysTick_CTRL_COUNTFLAG_Pos;
}

SysticClockSource SysticOperator::ClockSource()
{
	uint32_t masked = SysTick->CTRL & SysTick_CTRL_CLKSOURCE_Msk;
	masked >> SysTick_CTRL_CLKSOURCE_Pos;
	if (masked)
	{
		return SysticClockSource::Hclk;
	}

	return SysticClockSource::HclkDiv8;
}

void SysticOperator::SetClockSource(SysticClockSource value)
{
	/* 其实 HAL 中已经有一个 HAL_SYSTICK_CLKSourceConfig 函数用来干这个事了。
	* 只不过 HAL_SYSTICK_CLKSourceConfig 函数不太清晰。
	*/
	if (value == SysticClockSource::HclkDiv8)
	{
		// 清 0 表示使用 8 分频
		SysTick->CTRL &= ~SYSTICK_CLKSOURCE_HCLK;
	}
	else
	{
		// 置 1 表示不分频，让 HCLK 直接作为 Systick 的时钟源。
		SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK;
	}
}

uint32_t SysticOperator::ClockSourceFreq()
{
	uint32_t hclk_freq = HAL_RCC_GetHCLKFreq();
	if (ClockSource() == SysticClockSource::HclkDiv8)
	{
		return hclk_freq / 8;
	}

	return hclk_freq;
}

uint32_t SysticOperator::ReloadNum()
{
	uint32_t masked = SysTick->LOAD & SysTick_LOAD_RELOAD_Msk;
	return masked >> SysTick_LOAD_RELOAD_Pos;
}

uint32_t SysticOperator::CurrentValue()
{
	uint32_t masked = SysTick->VAL & SysTick_VAL_CURRENT_Msk;
	return masked >> SysTick_VAL_CURRENT_Pos;
}

void SysticOperator::NopLoopDelayForTicks(uint32_t tick_count)
{
	/* 这里不禁用操作系统的调度。不要让此函数耦合性太强。
	* 如果需要的话，禁用操作系统的调度这个操作应该放到本函数外，调用者自己执行。
	*/
	uint32_t old_tick = CurrentValue();
	uint32_t total_tick = 0;
	while (1)
	{
		uint32_t now_tick = CurrentValue();
		if (old_tick == now_tick)
		{
			// CPU 太快了，导致再次进入循环后 old_tick == now_tick
			continue;
		}

		uint32_t delta_tick = 0;
		if (old_tick > now_tick)
		{
			// 因为是减计数，所以此时没有发生环绕
			delta_tick = old_tick - now_tick;
		}
		else
		{
			// 发生了环绕
			// delta_tick = old_tick - (now_tick - reload)
			// delta_tick = old_tick - now_tick + reload
			delta_tick = old_tick - now_tick + ReloadNum();
		}

		total_tick += delta_tick;
		if (total_tick >= tick_count)
		{
			return;
		}

		old_tick = now_tick;
	}
}

void SysticOperator::NopLoopDelayForUs(uint32_t us_count)
{
	uint32_t freq = ClockSourceFreq();
	NopLoopDelayForTicks(freq / (uint32_t)1e6 * us_count);
}

void SysticOperator::NopLoopDelayForMs(uint32_t ms_count)
{
	for (uint32_t i = 0; i < ms_count; i++)
	{
		NopLoopDelayForUs(1000);
	}
}

void HAL_Delay(uint32_t Delay)
{
	g_systic_operator.NopLoopDelayForMs(Delay);
}
