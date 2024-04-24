#include "AtkKeyScanner.h"
#include<atk-stm32f103/AtkKey.h>
#include<hal-wrapper/clock/Delayer.h>

using namespace hal;
using namespace bsp;

std::vector<IKey *> GetKeyVector()
{
	static std::vector<IKey *> keys = {
		&atk::Key0::Instance(),
		&atk::Key1::Instance(),
		&atk::KeyWakeUp::Instance(),
	};

	return keys;
}

atk::AtkKeyScanner::AtkKeyScanner() :
	bsp::KeyScanner(GetKeyVector())
{

}

void atk::AtkKeyScanner::Delay(std::chrono::milliseconds num)
{
	hal::Delayer::Instance().Delay(num);
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
		if (AtkKeyScanner::Instance().HasKeyDownEvent(0))
		{
			RedDigitalLed::Instance().Toggle();
		}

		if (AtkKeyScanner::Instance().HasKeyDownEvent(1))
		{
			GreenDigitalLed::Instance().Toggle();
		}

		if (AtkKeyScanner::Instance().HasKeyDownEvent(2))
		{
			GreenDigitalLed::Instance().Toggle();
		}
	}
}
