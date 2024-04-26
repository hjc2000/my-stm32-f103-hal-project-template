#include"TestExtiKey.h"
#include<atk-stm32f103/bsp.h>

using namespace atk;

void TestExtiKey()
{
	BSP_Initialize();
	BSP_RedDigitalLed().TurnOn();
	while (1)
	{
		if (BSP_WakeUpKey().IsPressed())
		{
			BSP_RedDigitalLed().Toggle();
			BSP_GreenDigitalLed().Toggle();
			BSP_WakeUpKey().ClearPressedFlag();
		}
	}
}
