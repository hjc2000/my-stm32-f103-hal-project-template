#include "GpioPinPE5.h"
#include <base/Initializer.h>
#include <hal-wrapper/peripheral/gpio/GpioPinOptions.h>
#include <hal.h>

static base::Initializer _init{
	[]()
	{
		hal::GpioPinPE5::Instance();
	}};

GPIO_TypeDef *hal::GpioPinPE5::Port()
{
	return GPIOE;
}

uint32_t hal::GpioPinPE5::Pin()
{
	return GPIO_PIN_5;
}

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
