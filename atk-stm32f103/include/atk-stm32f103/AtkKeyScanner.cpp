#include "AtkKeyScanner.h"
#include<atk-stm32f103/Key.h>
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
