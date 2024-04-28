#include"TestIndependentWatchDog.h"
#include<atk-stm32f103/bsp.h>

using namespace atk;

void TestIndependentWatchDog()
{
	BSP_Delayer().Delay(std::chrono::milliseconds(500));
	BSP_RedDigitalLed().TurnOn();
	BSP_IndependentWatchDog().SetWatchDogTimeoutDuration(std::chrono::milliseconds(1000));

	while (1)
	{
		BSP_KeyScanner().ScanKeys();
		if (BSP_KeyScanner().HasKeyDownEvent((uint16_t)KeyIndex::Key0))
		{
			BSP_IndependentWatchDog().Feed();
		}

		if (BSP_KeyScanner().HasKeyDownEvent((uint16_t)KeyIndex::Key1))
		{
			BSP_IndependentWatchDog().Feed();
		}
	}
}
