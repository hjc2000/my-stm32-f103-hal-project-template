#include"Interrupt.h"

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

/// <summary>
///		中断处理函数
/// </summary>
extern "C"
{
	void EXTI0_IRQHandler()
	{

	}

	void EXTI1_IRQHandler()
	{

	}

	void EXTI2_IRQHandler()
	{

	}

	void EXTI3_IRQHandler()
	{

	}

	void EXTI4_IRQHandler()
	{

	}
}
