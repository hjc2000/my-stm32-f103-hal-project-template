#pragma once
#include<hal-wrapper/peripheral/gpio/GpioTypeDef.h>

namespace hal
{
	class GpioPinInitOptions
	{
	public:
		GpioPinMode _mode = GpioPinMode::Input;
		GpioPinPull _pull_mode = GpioPinPull::NoPull;
		GpioPinSpeed _speed = GpioPinSpeed::High;
	};
}
