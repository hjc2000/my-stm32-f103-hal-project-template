#include "GpioPinPA0.h"
#include <base/Initializer.h>
#include <hal-wrapper/peripheral/gpio/GpioPinOptions.h>
#include <hal.h>

static base::Initializer _init{
	[]()
	{
		hal::GpioPinPA0::Instance();
	}};

GPIO_TypeDef *hal::GpioPinPA0::Port()
{
	return GPIOA;
}

uint32_t hal::GpioPinPA0::Pin()
{
	return GPIO_PIN_0;
}

void hal::GpioPinPA0::Open(bsp::IGpioPinOptions const &options)
{
	if (_is_open)
	{
		return;
	}

	_is_open = true;

	__HAL_RCC_GPIOA_CLK_ENABLE();
	GPIO_InitTypeDef init = static_cast<hal::GpioPinOptions const &>(options);
	init.Pin = Pin();
	HAL_GPIO_Init(Port(), &init);
}

void hal::GpioPinPA0::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
