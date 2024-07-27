#include "TestIndependentWatchDog.h"
#include <bsp/bsp.h>

void TestIndependentWatchDog()
{
	DI_Delayer().Delay(std::chrono::milliseconds{500});
	DI_RedDigitalLed().TurnOn();
	DI_IndependentWatchDog().SetWatchDogTimeoutDuration(std::chrono::milliseconds(1000));

	while (true)
	{
		DI_KeyScanner().ScanKeys();
		if (DI_KeyScanner().HasKeyDownEvent((uint16_t)KeyIndex::Key0))
		{
			DI_IndependentWatchDog().Feed();
		}

		if (DI_KeyScanner().HasKeyDownEvent((uint16_t)KeyIndex::Key1))
		{
			DI_IndependentWatchDog().Feed();
		}
	}
}
