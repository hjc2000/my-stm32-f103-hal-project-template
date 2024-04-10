#include"Main.h"
#include<atk-stm32f103/Clock.h>
#include<atk-stm32f103/Key.h>
#include<atk-stm32f103/Led.h>
#include<hal-wrapper/Systic.h>
#include<hal-wrapper/peripheral/GpioPort.h>

using namespace hal;
using namespace atk;

void Main()
{
	HAL_Init();
	config_72mhz_hclk();
	RedDigitalLed::Instance().Initialize();
	GreenDigitalLed::Instance().Initialize();
	Key0::Instance().Initialize();
	Key1::Instance().Initialize();
	KeyWakeUp::Instance().Initialize();

	bool key0_has_been_handled = false;
	bool key1_has_been_handled = false;
	bool key_wake_up_has_been_handled = false;
	while (1)
	{
		/* 实现一个循环队列，检测到按键被按下，就将相应的事件入队，队列满后移除最开始的那个事件。
		* 这样检测按键事件时就能通过退队来检测了。
		*/
		if (Key0::Instance().KeyIsReallyDown() && !key0_has_been_handled)
		{
			key0_has_been_handled = true;
			RedDigitalLed::Instance().Toggle();
		}

		if (Key0::Instance().KeyIsReallyUp())
		{
			key0_has_been_handled = false;
		}

		if (Key1::Instance().KeyIsReallyDown() && !key1_has_been_handled)
		{
			key1_has_been_handled = true;
			GreenDigitalLed::Instance().Toggle();
		}

		if (Key1::Instance().KeyIsReallyUp())
		{
			key1_has_been_handled = false;
		}

		if (KeyWakeUp::Instance().KeyIsReallyDown() && !key_wake_up_has_been_handled)
		{
			key_wake_up_has_been_handled = true;
			GreenDigitalLed::Instance().Toggle();
		}

		if (KeyWakeUp::Instance().KeyIsReallyUp())
		{
			key_wake_up_has_been_handled = false;
		}
	}
}
