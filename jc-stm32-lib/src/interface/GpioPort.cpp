#include"GpioPort.h"

bool GpioPort::IsClockDisabled()
{
	return !IsClockEnabled();
}

void GpioPort::DigitalWritePin(GpioPin pin, bool value)
{
	GPIO_PinState state = value ? GPIO_PinState::GPIO_PIN_SET : GPIO_PinState::GPIO_PIN_RESET;
	HAL_GPIO_WritePin(port_addr, (uint16_t)pin, state);
}
