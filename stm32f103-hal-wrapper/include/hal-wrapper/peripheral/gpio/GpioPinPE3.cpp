#include "GpioPinPE3.h"
#include <base/Initializer.h>
#include <hal-wrapper/peripheral/gpio/GpioPinOptions.h>
#include <hal.h>

static base::Initializer _init{
	[]()
	{
		hal::GpioPinPE3::Instance();
	}};

GPIO_TypeDef *hal::GpioPinPE3::Port()
{
	return GPIOE;
}

uint32_t hal::GpioPinPE3::Pin()
{
	return GPIO_PIN_3;
}

void hal::GpioPinPE3::Open(bsp::IGpioPinOptions const &options)
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

void hal::GpioPinPE3::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
