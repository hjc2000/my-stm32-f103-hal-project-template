#include "GpioPinPB5.h"
#include <base/Initializer.h>
#include <hal-wrapper/peripheral/gpio/GpioPinOptions.h>
#include <hal.h>

static base::Initializer _init{
	[]()
	{
		hal::GpioPinPB5::Instance();
	}};

GPIO_TypeDef *hal::GpioPinPB5::Port()
{
	return GPIOB;
}

uint32_t hal::GpioPinPB5::Pin()
{
	return GPIO_PIN_5;
}

void hal::GpioPinPB5::Open(bsp::IGpioPinOptions const &options)
{
	if (_is_open)
	{
		return;
	}

	_is_open = true;

	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitTypeDef init = static_cast<hal::GpioPinOptions const &>(options);
	init.Pin = Pin();
	HAL_GPIO_Init(Port(), &init);
}

void hal::GpioPinPB5::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
