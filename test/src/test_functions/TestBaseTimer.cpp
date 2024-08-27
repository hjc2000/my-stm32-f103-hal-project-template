#include "TestBaseTimer.h"
#include <bsp-interface/di/delayer.h>
#include <bsp-interface/di/led.h>
#include <bsp/bsp.h>

using namespace bsp;

void TestBaseTimer()
{
    BSP::Initialize();
    BSP::BaseTimer().Initialize(std::chrono::milliseconds{1000});
    BSP::BaseTimer().SetPeriodElapsedCallback(
        []()
        {
            DI_GreenDigitalLed().Toggle();
        });

    BSP::BaseTimer().Start();

    while (true)
    {
        DI_RedDigitalLed().Toggle();
        DI_Delayer().Delay(std::chrono::seconds{1});
    }
}
