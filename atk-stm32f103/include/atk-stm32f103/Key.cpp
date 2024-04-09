#include "Key.h"
#include<hal-wrapper/GpioPort.h>

using namespace hal;

void atk::Key0::Initialize()
{
	auto &gpio = hal::GpioPortE::Instance();
	gpio.EnableClock();
	GpioPinOptions options;
	options._mode = GpioPinMode::Input;
	options._pull_mode = GpioPinPull::PullUp;
	options._speed = GpioPinSpeed::High;
	gpio.InitPin(GpioPin::Pin4, options);
}

void atk::Key0::Deinitialize()
{

}

bool atk::Key0::IsPressed()
{
	auto &gpio = hal::GpioPortE::Instance();

	// 被按下是低电平，否则是高电平
	return !gpio.DigitalReadPin(GpioPin::Pin4);
}
