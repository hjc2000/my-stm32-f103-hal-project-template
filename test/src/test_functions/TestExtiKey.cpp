#include "TestExtiKey.h"
#include <bsp-interface/di/led.h>
#include <bsp/bsp.h>

void TestExtiKey()
{
    DI_RedDigitalLed().TurnOn();
    while (1)
    {
        if (BSP::WakeUpKey().IsPressed())
        {
            DI_RedDigitalLed().Toggle();
            DI_GreenDigitalLed().Toggle();
            BSP::WakeUpKey().ClearPressedFlag();
        }
    }
}
