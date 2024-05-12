#pragma once
#include<GpioTypeDef.h>

namespace bsp
{
	class GpioPinInitOptions
	{
	public:
		GpioPinMode _mode = GpioPinMode::Input;
		GpioPinPull _pull_mode = GpioPinPull::NoPull;
		GpioPinSpeed _speed = GpioPinSpeed::High;
	};
}
