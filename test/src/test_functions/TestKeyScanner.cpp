#include "TestKeyScanner.h"
#include <bsp/bsp.h>

using namespace bsp;

void TestKeyScanner()
{
	while (true)
	{
		BSP::KeyScanner().ScanKeys();
		if (BSP::KeyScanner().HasKeyDownEvent((uint16_t)KeyIndex::Key0))
		{
			BSP::RedDigitalLed().Toggle();
		}

		if (BSP::KeyScanner().HasKeyDownEvent((uint16_t)KeyIndex::Key1))
		{
			BSP::GreenDigitalLed().Toggle();
		}
	}
}
