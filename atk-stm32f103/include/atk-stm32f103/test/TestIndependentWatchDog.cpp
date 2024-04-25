#include"TestIndependentWatchDog.h"
#include<atk-stm32f103/bsp.h>
#include<hal-wrapper/clock/Delayer.h>

void atk::TestIndependentWatchDog()
{
	BSP_Initialize();
	hal::Delayer::Instance().Delay(std::chrono::milliseconds(500));
	BSP_RedDigitalLed().TurnOn();
	IndependentWatchDog().SetWatchDogTimeoutDuration(std::chrono::milliseconds(1000));

	while (1)
	{
		BSP_KeyScanner().ScanKeys();
		if (BSP_KeyScanner().HasKeyDownEvent((uint16_t)KeyIndex::Key0))
		{
			IndependentWatchDog().Feed();
		}

		if (BSP_KeyScanner().HasKeyDownEvent((uint16_t)KeyIndex::Key1))
		{
			IndependentWatchDog().Feed();
		}

		if (BSP_KeyScanner().HasKeyDownEvent((uint16_t)KeyIndex::KeyWakeup))
		{
			IndependentWatchDog().Feed();
		}
	}
}
