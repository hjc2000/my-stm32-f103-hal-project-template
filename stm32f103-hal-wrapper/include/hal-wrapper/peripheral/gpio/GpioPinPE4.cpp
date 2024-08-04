#include "GpioPinPE4.h"
#include <base/Initializer.h>
#include <hal-wrapper/peripheral/gpio/GpioPinOptions.h>
#include <hal.h>

static base::Initializer _init{
	[]()
	{
		hal::GpioPinPE4::Instance();
	}};

GPIO_TypeDef *hal::GpioPinPE4::Port()
{
	return GPIOE;
}

uint32_t hal::GpioPinPE4::Pin()
{
	return GPIO_PIN_4;
}

void hal::GpioPinPE4::Open(bsp::IGpioPinOptions const &options)
{
	if (_is_open)
	{
		return;
	}

	_is_open = true;

	__HAL_RCC_GPIOE_CLK_ENABLE();
	GPIO_InitTypeDef init = static_cast<hal::GpioPinOptions const &>(options);
	init.Pin = Pin();
	HAL_GPIO_Init(Port(), &init);
}

void hal::GpioPinPE4::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
