#include "Key.h"
#include<hal-wrapper/GpioPort.h>
#include<hal-wrapper/Systic.h>

using namespace hal;

void atk::Key0::Initialize()
{
	GpioPortE::Instance().EnableClock();
	GpioPinOptions options;
	options._mode = GpioPinMode::Input;
	options._pull_mode = GpioPinPull::PullUp;
	options._speed = GpioPinSpeed::High;
	GpioPortE::Instance().InitPin(GpioPin::Pin4, options);
}

void atk::Key0::Deinitialize()
{

}

bool atk::Key0::KeyIsDown()
{
	// 被按下是低电平，否则是高电平
	return !GpioPortE::Instance().DigitalReadPin(GpioPin::Pin4);
}

bool atk::Key0::KeyIsReallyDown()
{
	if (!KeyIsDown())
	{
		return false;
	}

	Systic::NopLoopDelay(std::chrono::milliseconds(10));
	return KeyIsDown();
}

bool atk::Key0::KeyIsReallyUp()
{
	if (!KeyIsUp())
	{
		return false;
	}

	Systic::NopLoopDelay(std::chrono::milliseconds(10));
	return KeyIsUp();
}
