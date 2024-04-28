#include"Interrupt.h"
#include<FreeRTOS.h>
#include<task.h>

using namespace hal;

void hal::Interrupt::SetPriorityGroup(PreemptionPriorityGroup group)
{
	static bool have_set = false;
	if (have_set)
	{
		return;
	}

	have_set = true;
	HAL_NVIC_SetPriorityGrouping((uint32_t)group);
}

extern "C"
{
	/**
	* @brief  This function handles NMI exception.
	* @param  None
	* @retval None
	*/
	void NMI_Handler()
	{

	}

	/**
	* @brief  This function handles Hard Fault exception.
	* @param  None
	* @retval None
	*/
	void HardFault_Handler()
	{
		/* Go to infinite loop when Hard Fault exception occurs */
		while (1)
		{

		}
	}

	/**
	* @brief  This function handles Memory Manage exception.
	* @param  None
	* @retval None
	*/
	void MemManage_Handler()
	{
		/* Go to infinite loop when Memory Manage exception occurs */
		while (1)
		{

		}
	}

	/**
	* @brief  This function handles Bus Fault exception.
	* @param  None
	* @retval None
	*/
	void BusFault_Handler()
	{
		/* Go to infinite loop when Bus Fault exception occurs */
		while (1)
		{

		}
	}

	/**
	* @brief  This function handles Usage Fault exception.
	* @param  None
	* @retval None
	*/
	void UsageFault_Handler()
	{
		/* Go to infinite loop when Usage Fault exception occurs */
		while (1)
		{

		}
	}

	/**
	* @brief  This function handles Debug Monitor exception.
	* @param  None
	* @retval None
	*/
	void DebugMon_Handler()
	{

	}

	extern void xPortSysTickHandler();

	void SysTick_Handler()
	{
		HAL_IncTick();
		if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
		{
			xPortSysTickHandler();
		}
	}
}
