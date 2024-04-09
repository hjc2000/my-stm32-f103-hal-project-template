#include"Main.h"
#include<atk-stm32f103/Clock.h>
#include<atk-stm32f103/Key.h>
#include<atk-stm32f103/Led.h>
#include<hal-wrapper/GpioPort.h>
#include<hal-wrapper/Systic.h>

using namespace hal;
using namespace atk;

void Main()
{
	HAL_Init();
	config_72mhz_hclk();
	RedDigitalLed::Instance().Initialize();
	GreenDigitalLed::Instance().Initialize();
	Key0::Instance().Initialize();

	bool key0_has_been_handled = false;
	while (1)
	{
		if (Key0::Instance().KeyIsReallyDown() && !key0_has_been_handled)
		{
			key0_has_been_handled = true;
			RedDigitalLed::Instance().Toggle();
		}

		if (Key0::Instance().KeyIsReallyUp())
		{
			key0_has_been_handled = false;
		}
	}
}
