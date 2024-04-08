#include"hal-wrapper/GpioPort.h"

using namespace hal;

bool GpioPort::IsClockDisabled()
{
	return !IsClockEnabled();
}

void GpioPort::InitPin(GpioPin pin, GpioPinOptions const &options)
{
	GPIO_InitTypeDef gpio_init_options;
	gpio_init_options.Pin = (uint32_t)pin;
	gpio_init_options.Mode = (uint32_t)options._mode;
	gpio_init_options.Pull = (uint32_t)options._pull_mode;
	gpio_init_options.Speed = (uint32_t)options._speed;
	HAL_GPIO_Init(port_addr, &gpio_init_options);
}

void GpioPort::DigitalWritePin(GpioPin pin, bool value)
{
	GPIO_PinState state = value ? GPIO_PinState::GPIO_PIN_SET : GPIO_PinState::GPIO_PIN_RESET;
	HAL_GPIO_WritePin(port_addr, (uint16_t)pin, state);
}
