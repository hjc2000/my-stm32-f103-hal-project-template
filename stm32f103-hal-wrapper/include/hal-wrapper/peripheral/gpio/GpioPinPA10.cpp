#include "GpioPinPA10.h"
#include <base/Initializer.h>
#include <hal-wrapper/peripheral/gpio/GpioPinOptions.h>
#include <hal.h>

static base::Initializer _init{
	[]()
	{
		hal::GpioPinPA10::Instance();
	}};

GPIO_TypeDef *hal::GpioPinPA10::Port()
{
	return GPIOA;
}

uint32_t hal::GpioPinPA10::Pin()
{
	return GPIO_PIN_10;
}

std::string hal::GpioPinPA10::PinName() const
{
	return "PA10";
}

void hal::GpioPinPA10::Open(bsp::IGpioPinOptions const &options)
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

void hal::GpioPinPA10::Close()
{
	if (!_is_open)
	{
		return;
	}

	_is_open = false;
}
