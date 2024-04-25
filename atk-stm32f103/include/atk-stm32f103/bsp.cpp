#include"bsp.h"
#include<AtkClock.h>
#include<AtkKey.h>
#include<AtkLed.h>
#include<atomic>
#include<bsp-interface/KeyScanner.h>
#include<hal-wrapper/clock/Delayer.h>
#include<hal-wrapper/peripheral/independent-watch-dog/IndependentWatchDog.h>

void atk::BSP_Initialize()
{
	HAL_Init();
	config_72mhz_hclk();
}

bsp::IIndependentWatchDog &atk::BSP_IndependentWatchDog()
{
	return hal::IndependentWatchDog::Instance();
}

bsp::IDigitalLed &atk::BSP_RedDigitalLed()
{
	return atk::RedDigitalLed::Instance();
}

bsp::IDigitalLed &atk::BSP_GreenDigitalLed()
{
	return atk::GreenDigitalLed::Instance();
}

bsp::IKeyScanner &atk::BSP_KeyScanner()
{
	static std::atomic_bool initialized = false;
	static std::vector<bsp::IKey *> keys{ (size_t)KeyIndex::EnumEndFlag };
	if (!initialized)
	{
		keys[(uint16_t)KeyIndex::Key0] = &atk::Key0::Instance();
		keys[(uint16_t)KeyIndex::Key1] = &atk::Key1::Instance();
		keys[(uint16_t)KeyIndex::KeyWakeup] = &atk::KeyWakeUp::Instance();
	}

	static bsp::KeyScanner key_scanner{ keys, hal::Delayer::Instance() };

	initialized = true;
	return key_scanner;
}
