#include <base/Initializer.h>
#include <hal-wrapper/clock/SysTickClock.h>

void DI_Reset()
{
    HAL_NVIC_SystemReset();
}

bsp::ISysTick &DI_SysTick()
{
    return hal::SysTickClock::Instance();
}
