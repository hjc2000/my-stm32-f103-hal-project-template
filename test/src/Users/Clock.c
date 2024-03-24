#include"Clock.h"
#include<stm32f1xx_hal_cortex.h>

uint8_t systick_ctrl_get_count_flag()
{
	uint32_t masked = SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk;
	return masked >> SysTick_CTRL_COUNTFLAG_Pos;
}

uint8_t systick_ctrl_get_clock_source()
{
	uint32_t masked = SysTick->CTRL & SysTick_CTRL_CLKSOURCE_Msk;
	return masked >> SysTick_CTRL_CLKSOURCE_Pos;
}

void systick_ctrl_set_clock_source(uint8_t div8)
{
	/* 其实 HAL 中已经有一个 HAL_SYSTICK_CLKSourceConfig 函数用来干这个事了。
	* 只不过 HAL_SYSTICK_CLKSourceConfig 函数不太清晰。
	*/
	if (div8)
	{
		SysTick->CTRL &= ~SYSTICK_CLKSOURCE_HCLK;
	}
	else
	{
		SysTick->CTRL |= SYSTICK_CLKSOURCE_HCLK;
	}
}

uint32_t systick_load_get_reload()
{
	uint32_t masked = SysTick->LOAD & SysTick_LOAD_RELOAD_Msk;
	return masked >> SysTick_LOAD_RELOAD_Pos;
}

uint32_t systick_val_get_current()
{
	uint32_t masked = SysTick->VAL & SysTick_VAL_CURRENT_Msk;
	return masked >> SysTick_VAL_CURRENT_Pos;
}

void systick_nop_loop_delay_tick(uint32_t tick_count)
{
	/* 这里不禁用操作系统的调度。不要让此函数耦合性太强。
	* 如果需要的话，禁用操作系统的调度这个操作应该放到本函数外，调用者自己执行。
	*/
	uint32_t old_tick = systick_val_get_current();
	uint32_t total_tick = 0;
	while (1)
	{
		uint32_t now_tick = systick_val_get_current();
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
			delta_tick = old_tick - now_tick + systick_load_get_reload();
		}

		total_tick += delta_tick;
		if (total_tick >= tick_count)
		{
			return;
		}

		old_tick = now_tick;
	}
}

void systick_nop_loop_delay_us(uint32_t us_count)
{

}
