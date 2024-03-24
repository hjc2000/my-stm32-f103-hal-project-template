#include"Clock.h"

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
