#include "GpioPin.h"
#include <base/Initializer.h>
#include <hal-wrapper/peripheral/gpio/GpioPinOptions.h>
#include <hal.h>

static base::Initializer _init{
	[]()
	{
		bsp::GpioPinPB5::Instance();
	}};

void bsp::GpioPinPB5::Open(bsp::IGpioPinOptions const &options)
{
	if (_is_open)
	{
		return;
	}

	_is_open = true;

	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitTypeDef init = static_cast<hal::GpioPinOptions const &>(options);
	init.Pin = GPIO_PIN_5;
	HAL_GPIO_Init(GPIOB, &init);
}

void bsp::GpioPinPB5::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}

bool bsp::GpioPinPB5::ReadPin()
{
	GPIO_PinState pin_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5);
	if (pin_state == GPIO_PinState::GPIO_PIN_SET)
	{
		return true;
	}

	return false;
}

void bsp::GpioPinPB5::WritePin(bool value)
{
	GPIO_PinState state = value ? GPIO_PinState::GPIO_PIN_SET : GPIO_PinState::GPIO_PIN_RESET;
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, state);
}

void bsp::GpioPinPB5::TogglePin()
{
	HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_5);
}
