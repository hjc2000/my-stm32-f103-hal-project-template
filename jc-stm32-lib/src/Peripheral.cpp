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

void GpioPortA::InitPin(GpioPin pin, GpioPinOptions const &options)
{
	GPIO_InitTypeDef gpio_init_options;
	gpio_init_options.Pin = (uint32_t)pin;
	gpio_init_options.Mode = (uint32_t)options.mode;
	gpio_init_options.Pull = (uint32_t)options.pull_mode;
	gpio_init_options.Speed = (uint32_t)options.speed;
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

void GpioPortB::InitPin(GpioPin pin, GpioPinOptions const &options)
{
	GPIO_InitTypeDef gpio_init_options;
	gpio_init_options.Pin = (uint32_t)pin;
	gpio_init_options.Mode = (uint32_t)options.mode;
	gpio_init_options.Pull = (uint32_t)options.pull_mode;
	gpio_init_options.Speed = (uint32_t)options.speed;
	HAL_GPIO_Init(GPIOB, &gpio_init_options);
}

GpioPortB g_gpio_port_b{};





bool GpioPortE::IsClockEnabled()
{
	return __HAL_RCC_GPIOE_IS_CLK_ENABLED();
}

void GpioPortE::EnableClock()
{
	__HAL_RCC_GPIOE_CLK_ENABLE();
}

void GpioPortE::DisableClock()
{
	__HAL_RCC_GPIOE_CLK_DISABLE();
}

void GpioPortE::InitPin(GpioPin pin, GpioPinOptions const &options)
{
	GPIO_InitTypeDef gpio_init_options;
	gpio_init_options.Pin = (uint32_t)pin;
	gpio_init_options.Mode = (uint32_t)options.mode;
	gpio_init_options.Pull = (uint32_t)options.pull_mode;
	gpio_init_options.Speed = (uint32_t)options.speed;
	HAL_GPIO_Init(GPIOE, &gpio_init_options);
}

GpioPortE g_gpio_port_e{};
