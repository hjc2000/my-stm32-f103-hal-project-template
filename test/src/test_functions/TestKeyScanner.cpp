#include"TestKeyScanner.h"
#include<atk-stm32f103/bsp.h>

using namespace bsp;
using namespace atk;

void TestKeyScanner()
{
	while (1)
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
