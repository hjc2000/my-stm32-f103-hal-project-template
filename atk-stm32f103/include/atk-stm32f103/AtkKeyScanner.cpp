#include "AtkKeyScanner.h"
#include<atk-stm32f103/AtkKey.h>
#include<hal-wrapper/clock/Delayer.h>

using namespace hal;
using namespace bsp;

void atk::AtkKeyScanner::Delay(std::chrono::milliseconds num)
{
	hal::Delayer::Instance().Delay(num);
}

bsp::IKey **atk::AtkKeyScanner::KeyList()
{
	static IKey *keys[] = {
		&Key0::Instance(),
		&Key1::Instance(),
		&KeyWakeUp::Instance(),
	};

	return keys;
}

#include<atk-stm32f103/AtkClock.h>
#include<AtkLed.h>

void atk::TestKeyScanner()
{
	HAL_Init();
	config_72mhz_hclk();

	while (1)
	{
		AtkKeyScanner::Instance().ScanKeys();
		auto key_down_events = AtkKeyScanner::Instance().GetKeyDownEvents();

		if (key_down_events[0])
		{
			RedDigitalLed::Instance().Toggle();
		}

		if (key_down_events[1])
		{
			GreenDigitalLed::Instance().Toggle();
		}

		if (key_down_events[2])
		{
			GreenDigitalLed::Instance().Toggle();
		}
	}
}
