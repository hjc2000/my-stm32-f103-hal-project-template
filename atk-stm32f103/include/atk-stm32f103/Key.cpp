#include "Key.h"

using namespace hal;

#pragma region Key0
void atk::Key0::Initialize()
{
	Port().EnableClock();
	GpioPinOptions options;
	options._mode = GpioPinMode::Input;
	options._pull_mode = GpioPinPull::PullUp;
	options._speed = GpioPinSpeed::High;
	Port().InitPin(GpioPin::Pin4, options);
}

void atk::Key0::Deinitialize()
{

}

bool atk::Key0::KeyIsDown()
{
	// 被按下是低电平，否则是高电平
	return !Port().DigitalReadPin(GpioPin::Pin4);
}
#pragma endregion

#pragma region Key1
void atk::Key1::Initialize()
{
	Port().EnableClock();
	GpioPinOptions options;
	options._mode = GpioPinMode::Input;
	options._pull_mode = GpioPinPull::PullUp;
	options._speed = GpioPinSpeed::High;
	Port().InitPin(GpioPin::Pin3, options);
}

void atk::Key1::Deinitialize()
{

}

bool atk::Key1::KeyIsDown()
{
	// 被按下是低电平，否则是高电平
	return !Port().DigitalReadPin(GpioPin::Pin3);
}
#pragma endregion

#pragma region KeyWakeUp
void atk::KeyWakeUp::Initialize()
{
	Port().EnableClock();
	GpioPinOptions options;
	options._mode = GpioPinMode::Input;
	options._pull_mode = GpioPinPull::PullDown;
	options._speed = GpioPinSpeed::High;
	Port().InitPin(GpioPin::Pin0, options);
}

void atk::KeyWakeUp::Deinitialize()
{

}

bool atk::KeyWakeUp::KeyIsDown()
{
	// 被按下是高电平
	return Port().DigitalReadPin(GpioPin::Pin0);
}
#pragma endregion
