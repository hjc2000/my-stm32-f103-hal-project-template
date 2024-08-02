#include "GpioPinOptions.h"

hal::GpioPinOptions::operator GPIO_InitTypeDef() const
{
	switch (WorkMode())
	{
	default:
	case bsp::IGpioPinWorkMode::Gpio:
	{
		break;
	}
	case bsp::IGpioPinWorkMode::AlternateFunction:
	{
		break;
	}
	case bsp::IGpioPinWorkMode::Event:
	{
		break;
	}
	case bsp::IGpioPinWorkMode::Analog:
	{
		break;
	}
	}

	return _hal_gpio_init;
}

bsp::IGpioPinWorkMode hal::GpioPinOptions::WorkMode() const
{
	return _work_mode;
}

void hal::GpioPinOptions::SetWorkMode(bsp::IGpioPinWorkMode value)
{
	_work_mode = value;
}

bsp::IGpioPinTriggerEdge hal::GpioPinOptions::TriggerEdge() const
{
	return _trigger_edge;
}

void hal::GpioPinOptions::SetTriggerEdge(bsp::IGpioPinTriggerEdge value)
{
	_trigger_edge = value;
}

bsp::IGpioPinPullMode hal::GpioPinOptions::PullMode() const
{
	switch (_hal_gpio_init.Pull)
	{
	default:
	case GPIO_NOPULL:
	{
		return bsp::IGpioPinPullMode::NoPull;
	}
	case GPIO_PULLUP:
	{
		return bsp::IGpioPinPullMode::PullUp;
	}
	case GPIO_PULLDOWN:
	{
		return bsp::IGpioPinPullMode::PullDown;
	}
	}
}

void hal::GpioPinOptions::SetPullMode(bsp::IGpioPinPullMode value)
{
	switch (value)
	{
	default:
	case bsp::IGpioPinPullMode::NoPull:
	{
		_hal_gpio_init.Pull = GPIO_NOPULL;
		break;
	}
	case bsp::IGpioPinPullMode::PullUp:
	{
		_hal_gpio_init.Pull = GPIO_PULLUP;
		break;
	}
	case bsp::IGpioPinPullMode::PullDown:
	{
		_hal_gpio_init.Pull = GPIO_PULLDOWN;
		break;
	}
	}
}

int hal::GpioPinOptions::SpeedLevel() const
{
	switch (_hal_gpio_init.Speed)
	{
	case GPIO_SPEED_FREQ_LOW:
	{
		return 0;
	}
	case GPIO_SPEED_FREQ_MEDIUM:
	{
		return 1;
	}
	default:
	case GPIO_SPEED_FREQ_HIGH:
	{
		return 2;
	}
	}
}

void hal::GpioPinOptions::SetSpeedLevel(int value)
{
	switch (value)
	{
	case 0:
	{
		_hal_gpio_init.Speed = GPIO_SPEED_FREQ_LOW;
		break;
	}
	case 1:
	{
		_hal_gpio_init.Speed = GPIO_SPEED_FREQ_MEDIUM;
		break;
	}
	default:
	case 2:
	{
		_hal_gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
		break;
	}
	}
}
