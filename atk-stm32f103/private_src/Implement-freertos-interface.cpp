#include"FreeRTOSConfig.h"
#include<Systic.h>
#include<hal.h>

uint32_t freertos_get_cpu_freq()
{
	return HAL_RCC_GetHCLKFreq();
}

uint32_t freertos_get_systic_clock_freq()
{
	return atk::Systic::ClockSourceFreq();
}
