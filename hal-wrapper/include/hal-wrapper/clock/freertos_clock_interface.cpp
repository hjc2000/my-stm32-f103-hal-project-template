#include"freertos_clock_interface.h"
#include<hal-wrapper/clock/Systic.h>

using namespace hal;

uint32_t freertos_get_cpu_freq()
{
	return SystemCoreClock;
}

uint32_t freertos_get_systic_clock_freq()
{
	return Systic::ClockSourceFreq();
}
