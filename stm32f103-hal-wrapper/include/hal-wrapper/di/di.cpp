#include <base/Initializer.h>
#include <bsp-interface/di.h>
#include <hal-wrapper/clock/SysTickClock.h>

void DI_Reset()
{
	HAL_NVIC_SystemReset();
	DI_InterruptSwitch();
}

bsp::ISysTick &DI_SysTick()
{
	return hal::SysTickClock::Instance();
}
