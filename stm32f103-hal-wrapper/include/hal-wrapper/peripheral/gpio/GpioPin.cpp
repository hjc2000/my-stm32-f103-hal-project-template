#include "GpioPin.h"

bool hal::GpioPin::ReadPin()
{
	GPIO_PinState pin_state = HAL_GPIO_ReadPin(Port(), Pin());
	if (pin_state == GPIO_PinState::GPIO_PIN_SET)
	{
		return true;
	}

	return false;
}

void hal::GpioPin::WritePin(bool value)
{
	GPIO_PinState state = value ? GPIO_PinState::GPIO_PIN_SET : GPIO_PinState::GPIO_PIN_RESET;
	HAL_GPIO_WritePin(Port(), Pin(), state);
}

void hal::GpioPin::TogglePin()
{
	HAL_GPIO_TogglePin(Port(), Pin());
}
