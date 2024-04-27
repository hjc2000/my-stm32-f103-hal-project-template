#include"FreeRTOSConfig.h"
#include<hal.h>

uint32_t get_cpu_freq()
{
	return SystemCoreClock;
}
