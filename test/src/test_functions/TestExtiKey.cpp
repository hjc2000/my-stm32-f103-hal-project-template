#include"TestExtiKey.h"
#include<atk-stm32f103/bsp.h>

using namespace atk;

void TestExtiKey()
{
	BSP::RedDigitalLed().TurnOn();
	while (1)
	{
		if (BSP::WakeUpKey().IsPressed())
		{
			BSP::RedDigitalLed().Toggle();
			BSP::GreenDigitalLed().Toggle();
			BSP::WakeUpKey().ClearPressedFlag();
		}
	}
}
