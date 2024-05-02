#include<FreeRTOS.h>
#include<hal.h>
#include<task.h>

extern "C"
{
	void xPortSysTickHandler();

	void SysTick_Handler()
	{
		HAL_IncTick();
		if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
		{
			xPortSysTickHandler();
		}
	}
}
