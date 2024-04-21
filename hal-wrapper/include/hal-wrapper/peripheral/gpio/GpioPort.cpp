#include"GpioPort.h"

using namespace hal;

void GpioPort::InitPin(GpioPin pin, GpioPinInitOptions const &options)
{
	GPIO_InitTypeDef gpio_init_options;
	gpio_init_options.Pin = (uint32_t)pin;
	gpio_init_options.Mode = (uint32_t)options._mode;
	gpio_init_options.Pull = (uint32_t)options._pull_mode;
	gpio_init_options.Speed = (uint32_t)options._speed;
	HAL_GPIO_Init(HardwareInstance(), &gpio_init_options);
}

void GpioPort::DigitalWritePin(GpioPin pin, bool value)
{
	GPIO_PinState state = value ? GPIO_PinState::GPIO_PIN_SET : GPIO_PinState::GPIO_PIN_RESET;
	HAL_GPIO_WritePin(HardwareInstance(), (uint16_t)pin, state);
}

bool GpioPort::DigitalReadPin(GpioPin pin)
{
	GPIO_PinState pin_state = HAL_GPIO_ReadPin(HardwareInstance(), (uint16_t)pin);
	if (pin_state == GPIO_PinState::GPIO_PIN_SET)
	{
		return true;
	}

	return false;
}

void GpioPort::DigitalTogglePin(GpioPin pin)
{
	HAL_GPIO_TogglePin(HardwareInstance(), (uint16_t)pin);
}

#pragma region GpioPortA
GPIO_TypeDef *GpioPortA::HardwareInstance()
{
	return GPIOA;
}

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
GPIO_TypeDef *GpioPortB::HardwareInstance()
{
	return GPIOB;
}

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
GPIO_TypeDef *GpioPortC::HardwareInstance()
{
	return GPIOC;
}

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
GPIO_TypeDef *GpioPortD::HardwareInstance()
{
	return GPIOD;
}

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
GPIO_TypeDef *GpioPortE::HardwareInstance()
{
	return GPIOE;
}

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
