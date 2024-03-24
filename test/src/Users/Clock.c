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

void systick_nop_loop_delay_us(uint32_t us_count)
{

}
