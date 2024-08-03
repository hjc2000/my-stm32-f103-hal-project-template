#include "GpioPinPE5.h"
#include <base/Initializer.h>
#include <hal-wrapper/peripheral/gpio/GpioPinOptions.h>
#include <hal.h>

static base::Initializer _init{
	[]()
	{
		hal::GpioPinPE5::Instance();
	}};

void hal::GpioPinPE5::Open(bsp::IGpioPinOptions const &options)
{
	if (_is_open)
	{
		return;
	}

	_is_open = true;

	__HAL_RCC_GPIOE_CLK_ENABLE();
	GPIO_InitTypeDef init = static_cast<hal::GpioPinOptions const &>(options);
	init.Pin = GPIO_PIN_5;
	HAL_GPIO_Init(GPIOE, &init);
}

void hal::GpioPinPE5::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}

bool hal::GpioPinPE5::ReadPin()
{
	GPIO_PinState pin_state = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5);
	if (pin_state == GPIO_PinState::GPIO_PIN_SET)
	{
		return true;
	}

	return false;
}

void hal::GpioPinPE5::WritePin(bool value)
{
	GPIO_PinState state = value ? GPIO_PinState::GPIO_PIN_SET : GPIO_PinState::GPIO_PIN_RESET;
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, state);
}

void hal::GpioPinPE5::TogglePin()
{
	HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_5);
}
