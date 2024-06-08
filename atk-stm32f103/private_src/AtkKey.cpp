#include "AtkKey.h"

using namespace bsp;
using namespace hal;

#pragma region Key0
bsp::Key0::Key0()
{
	using namespace bsp;
	Port().EnableClock();
	GpioPinConfig options;
	options.SetPin(hal::GpioPinConfig::PinEnum::Pin4);
	options.SetMode(hal::GpioPinConfig::ModeOption::Input);
	options.SetPull(hal::GpioPinConfig::PullOption::PullUp);
	options.SetSpeed(hal::GpioPinConfig::SpeedOption::High);
	Port().InitPin(options);
}

bool bsp::Key0::KeyIsDown()
{
	// 被按下是低电平，否则是高电平
	return !Port().DigitalReadPin(hal::GpioPinConfig::PinEnum::Pin4);
}
#pragma endregion

#pragma region Key1
bsp::Key1::Key1()
{
	using namespace bsp;
	Port().EnableClock();
	GpioPinConfig options;
	options.SetPin(hal::GpioPinConfig::PinEnum::Pin3);
	options.SetMode(hal::GpioPinConfig::ModeOption::Input);
	options.SetPull(hal::GpioPinConfig::PullOption::PullUp);
	options.SetSpeed(hal::GpioPinConfig::SpeedOption::High);
	Port().InitPin(options);
}

bool bsp::Key1::KeyIsDown()
{
	// 被按下是低电平，否则是高电平
	return !Port().DigitalReadPin(hal::GpioPinConfig::PinEnum::Pin3);
}
#pragma endregion
