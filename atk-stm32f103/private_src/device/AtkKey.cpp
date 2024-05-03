#include "AtkKey.h"

using namespace hal;

#pragma region Key0
atk::Key0::Key0()
{
	using namespace hal;
	Port().EnableClock();
	GpioPinInitOptions options;
	options._mode = GpioPinMode::Input;
	options._pull_mode = GpioPinPull::PullUp;
	options._speed = GpioPinSpeed::High;
	Port().InitPin(GpioPin::Pin4, options);
}

bool atk::Key0::KeyIsDown()
{
	// 被按下是低电平，否则是高电平
	return !Port().DigitalReadPin(GpioPin::Pin4);
}
#pragma endregion

#pragma region Key1
atk::Key1::Key1()
{
	using namespace hal;
	Port().EnableClock();
	GpioPinInitOptions options;
	options._mode = GpioPinMode::Input;
	options._pull_mode = GpioPinPull::PullUp;
	options._speed = GpioPinSpeed::High;
	Port().InitPin(GpioPin::Pin3, options);
}

bool atk::Key1::KeyIsDown()
{
	// 被按下是低电平，否则是高电平
	return !Port().DigitalReadPin(GpioPin::Pin3);
}
#pragma endregion
