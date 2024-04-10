#include "Key.h"
#include<hal-wrapper/Systic.h>
#include<hal-wrapper/peripheral/GpioPort.h>

using namespace hal;

#pragma region Key0
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
#pragma endregion
