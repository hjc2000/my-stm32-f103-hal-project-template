#include"Peripheral.h"

bool GpioPortA::IsClockEnabled()
{
	return __HAL_RCC_GPIOA_IS_CLK_ENABLED();
}

void GpioPortA::EnableClock()
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
}

void GpioPortA::DisableClock()
{
	__HAL_RCC_GPIOA_CLK_DISABLE();
}

void GpioPortA::InitPin(GpioPin pin, GpioPinMode mode, GpioPinPull pull_mode, GpioPinSpeed speed)
{
	GPIO_InitTypeDef gpio_init_options;
	gpio_init_options.Pin = (uint32_t)pin;
	gpio_init_options.Mode = (uint32_t)mode;
	gpio_init_options.Pull = (uint32_t)pull_mode;
	gpio_init_options.Speed = (uint32_t)speed;
	HAL_GPIO_Init(GPIOA, &gpio_init_options);
}

GpioPortA g_gpio_port_a{};





bool GpioPortB::IsClockEnabled()
{
	return __HAL_RCC_GPIOB_IS_CLK_ENABLED();
}

void GpioPortB::EnableClock()
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
}

void GpioPortB::DisableClock()
{
	__HAL_RCC_GPIOB_CLK_DISABLE();
}

void GpioPortB::InitPin(GpioPin pin, GpioPinMode mode, GpioPinPull pull_mode, GpioPinSpeed speed)
{
	GPIO_InitTypeDef gpio_init_options;
	gpio_init_options.Pin = (uint32_t)pin;
	gpio_init_options.Mode = (uint32_t)mode;
	gpio_init_options.Pull = (uint32_t)pull_mode;
	gpio_init_options.Speed = (uint32_t)speed;
	HAL_GPIO_Init(GPIOB, &gpio_init_options);
}

GpioPortB g_gpio_port_b{};
