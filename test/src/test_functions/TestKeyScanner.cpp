#include"TestKeyScanner.h"
#include<atk-stm32f103/bsp.h>

using namespace bsp;
using namespace atk;

void TestKeyScanner()
{
	BSP_Initialize();
	while (1)
	{
		BSP_KeyScanner().ScanKeys();
		if (BSP_KeyScanner().HasKeyDownEvent((uint16_t)KeyIndex::Key0))
		{
			BSP_RedDigitalLed().Toggle();
		}

		if (BSP_KeyScanner().HasKeyDownEvent((uint16_t)KeyIndex::Key1))
		{
			BSP_GreenDigitalLed().Toggle();
		}
	}
}
