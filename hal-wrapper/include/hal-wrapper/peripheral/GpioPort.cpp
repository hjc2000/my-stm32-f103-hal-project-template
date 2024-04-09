#include"hal-wrapper/peripheral/GpioPort.h"

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
	HAL_GPIO_Init(_port_addr, &gpio_init_options);
}

void GpioPort::DigitalWritePin(GpioPin pin, bool value)
{
	GPIO_PinState state = value ? GPIO_PinState::GPIO_PIN_SET : GPIO_PinState::GPIO_PIN_RESET;
	HAL_GPIO_WritePin(_port_addr, (uint16_t)pin, state);
}

bool GpioPort::DigitalReadPin(GpioPin pin)
{
	GPIO_PinState pin_state = HAL_GPIO_ReadPin(_port_addr, (uint16_t)pin);
	if (pin_state == GPIO_PinState::GPIO_PIN_SET)
	{
		return true;
	}

	return false;
}

void GpioPort::DigitalTogglePin(GpioPin pin)
{
	HAL_GPIO_TogglePin(_port_addr, (uint16_t)pin);
}

#pragma region GpioPortA
bool GpioPortA::IsClockEnabled()
{
	return __HAL_RCC_GPIOA_IS_CLK_ENABLED();
}

void GpioPortA::EnableClock()
{
	if (IsClockEnabled())
	{
		return;
	}

	__HAL_RCC_GPIOA_CLK_ENABLE();
}

void GpioPortA::DisableClock()
{
	if (IsClockDisabled())
	{
		return;
	}

	__HAL_RCC_GPIOA_CLK_DISABLE();
}
#pragma endregion

#pragma region GpioPortB
bool GpioPortB::IsClockEnabled()
{
	return __HAL_RCC_GPIOB_IS_CLK_ENABLED();
}

void GpioPortB::EnableClock()
{
	if (IsClockEnabled())
	{
		return;
	}

	__HAL_RCC_GPIOB_CLK_ENABLE();
}

void GpioPortB::DisableClock()
{
	if (IsClockDisabled())
	{
		return;
	}

	__HAL_RCC_GPIOB_CLK_DISABLE();
}
#pragma endregion

#pragma region GpioPortC
bool GpioPortC::IsClockEnabled()
{
	return __HAL_RCC_GPIOC_IS_CLK_ENABLED();
}

void GpioPortC::EnableClock()
{
	if (IsClockEnabled())
	{
		return;
	}

	__HAL_RCC_GPIOC_CLK_ENABLE();
}

void GpioPortC::DisableClock()
{
	if (IsClockDisabled())
	{
		return;
	}

	__HAL_RCC_GPIOC_CLK_DISABLE();
}
#pragma endregion

#pragma region GpioPortD
bool GpioPortD::IsClockEnabled()
{
	return __HAL_RCC_GPIOD_IS_CLK_ENABLED();
}

void GpioPortD::EnableClock()
{
	if (IsClockEnabled())
	{
		return;
	}

	__HAL_RCC_GPIOD_CLK_ENABLE();
}

void GpioPortD::DisableClock()
{
	if (IsClockDisabled())
	{
		return;
	}

	__HAL_RCC_GPIOD_CLK_DISABLE();
}
#pragma endregion

#pragma region GpioPortE
bool GpioPortE::IsClockEnabled()
{
	return __HAL_RCC_GPIOE_IS_CLK_ENABLED();
}

void GpioPortE::EnableClock()
{
	if (IsClockEnabled())
	{
		return;
	}

	__HAL_RCC_GPIOE_CLK_ENABLE();
}

void GpioPortE::DisableClock()
{
	if (IsClockDisabled())
	{
		return;
	}

	__HAL_RCC_GPIOE_CLK_DISABLE();
}
#pragma endregion
