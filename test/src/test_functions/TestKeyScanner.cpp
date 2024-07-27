#include "TestKeyScanner.h"
#include <bsp/bsp.h>

using namespace bsp;

void TestKeyScanner()
{
	while (true)
	{
		DI_KeyScanner().ScanKeys();
		if (DI_KeyScanner().HasKeyDownEvent(static_cast<int>(KeyIndex::Key0)))
		{
			BSP::RedDigitalLed().Toggle();
		}

		if (DI_KeyScanner().HasKeyDownEvent(static_cast<int>(KeyIndex::Key1)))
		{
			BSP::GreenDigitalLed().Toggle();
		}
	}
}
