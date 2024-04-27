#include"stm32f1xx_it.h"
#include<hal.h>

std::function<void()> g_on_nmi;
std::function<void()> g_on_hard_fault;
std::function<void()> g_on_memory_nanage;
std::function<void()> g_on_bus_fault;
std::function<void()> g_on_usage_fault;
std::function<void()> g_on_debug_mon;
std::function<void()> g_on_systic;

std::function<void()> g_on_exti0_interrupt;
std::function<void()> g_on_exti1_interrupt;
std::function<void()> g_on_exti2_interrupt;
std::function<void()> g_on_exti3_interrupt;
std::function<void()> g_on_exti4_interrupt;

/**
* @brief   This function handles NMI exception.
* @param  None
* @retval None
*/
void NMI_Handler()
{
	if (g_on_nmi)
	{
		g_on_nmi();
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
	if (g_on_hard_fault)
	{
		g_on_hard_fault();
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
	if (g_on_memory_nanage)
	{
		g_on_memory_nanage();
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
	if (g_on_bus_fault)
	{
		g_on_bus_fault();
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
	if (g_on_usage_fault)
	{
		g_on_usage_fault();
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
	if (g_on_debug_mon)
	{
		g_on_debug_mon();
	}
}

/**
* @brief  This function handles SysTick Handler.
* @param  None
* @retval None
*/
void SysTick_Handler()
{
	if (g_on_systic)
	{
		g_on_systic();
	}

	HAL_IncTick();
}

void EXTI0_IRQHandler()
{
	if (g_on_exti0_interrupt)
	{
		g_on_exti0_interrupt();
	}
}

void EXTI1_IRQHandler()
{
	if (g_on_exti1_interrupt)
	{
		g_on_exti1_interrupt();
	}
}

void EXTI2_IRQHandler()
{
	if (g_on_exti2_interrupt)
	{
		g_on_exti2_interrupt();
	}
}

void EXTI3_IRQHandler()
{
	if (g_on_exti3_interrupt)
	{
		g_on_exti3_interrupt();
	}
}

void EXTI4_IRQHandler()
{
	if (g_on_exti4_interrupt)
	{
		g_on_exti4_interrupt();
	}
}
