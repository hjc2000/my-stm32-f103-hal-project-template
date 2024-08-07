#include "FreeRTOSConfig.h"
#include <FreeRTOS.h>
#include <hal-wrapper/clock/SysTickClock.h>
#include <hal.h>
#include <task.h>

extern "C"
{
	uint32_t freertos_get_systic_clock_freq(uint8_t sync_to_cpu)
	{
		return hal::SysTickClock::Instance().Frequency();
	}

	void SysTick_Handler()
	{
		HAL_IncTick();
		if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
		{
			xPortSysTickHandler();
		}
	}
}
