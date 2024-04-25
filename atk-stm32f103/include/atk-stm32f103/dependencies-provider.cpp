#include"dependencies-provider.h"
#include<AtkLed.h>
#include<atk-stm32f103/AtkKey.h>
#include<bsp-interface/KeyScanner.h>
#include<hal-wrapper/clock/Delayer.h>

bsp::IDigitalLed &RedDigitalLed()
{
	return atk::RedDigitalLed::Instance();
}

bsp::IDigitalLed &GreenDigitalLed()
{
	return atk::GreenDigitalLed::Instance();
}

bsp::IKeyScanner &KeyScanner()
{
	static std::vector<bsp::IKey *> keys = {
		&atk::Key0::Instance(),
		&atk::Key1::Instance(),
		&atk::KeyWakeUp::Instance(),
	};

	static bsp::KeyScanner key_scanner{ keys, &hal::Delayer::Instance() };
	return key_scanner;
}
