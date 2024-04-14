#pragma once
#include<hal-wrapper/interrupt/PreemptionPriorityGroup.h>

namespace hal
{
	class Interrupt
	{
	public:
		void SetPriorityGroup(PreemptionPriorityGroup group)
		{
			HAL_NVIC_SetPriorityGrouping((uint32_t)group);
		}
	};
}