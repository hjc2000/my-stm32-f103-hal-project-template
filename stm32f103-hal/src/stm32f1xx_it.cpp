#include"stm32f1xx_it.h"
#include<hal.h>

std::function<void()> _on_nmi;
std::function<void()> _on_hard_fault;
std::function<void()> _on_memory_nanage;
std::function<void()> _on_bus_fault;
std::function<void()> _on_usage_fault;
std::function<void()> _on_debug_mon;
std::function<void()> _on_systic;

/**
* @brief   This function handles NMI exception.
* @param  None
* @retval None
*/
void NMI_Handler()
{
	if (_on_nmi)
	{
		_on_nmi();
	}
}

/**
* @brief  This function handles Hard Fault exception.
* @param  None
* @retval None
*/
void HardFault_Handler()
{
	/* Go to infinite loop when Hard Fault exception occurs */
	if (_on_hard_fault)
	{
		_on_hard_fault();
	}

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
	if (_on_memory_nanage)
	{
		_on_memory_nanage();
	}

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
	if (_on_bus_fault)
	{
		_on_bus_fault();
	}

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
	if (_on_usage_fault)
	{
		_on_usage_fault();
	}

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
	if (_on_debug_mon)
	{
		_on_debug_mon();
	}
}

/**
* @brief  This function handles SysTick Handler.
* @param  None
* @retval None
*/
void SysTick_Handler()
{
	if (_on_systic)
	{
		_on_systic();
	}

	HAL_IncTick();
}
