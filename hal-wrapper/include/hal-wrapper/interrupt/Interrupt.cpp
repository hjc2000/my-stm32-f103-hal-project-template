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
