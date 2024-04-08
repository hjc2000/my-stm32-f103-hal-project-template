#include"Peripheral.h"

#ifdef GPIOA
class GpioPortA :public GpioPort
{
public:
	GpioPortA()
	{
		port_addr = GPIOA;
	}

	static GpioPortA &Instance()
	{
		static GpioPortA port{};
		return port;
	}

public:
	bool IsClockEnabled() override
	{
		return __HAL_RCC_GPIOA_IS_CLK_ENABLED();
	}

	void EnableClock() override
	{
		__HAL_RCC_GPIOA_CLK_ENABLE();
	}

	void DisableClock() override
	{
		__HAL_RCC_GPIOA_CLK_DISABLE();
	}

	void InitPin(GpioPin pin, GpioPinOptions const &options) override
	{
		GPIO_InitTypeDef gpio_init_options;
		gpio_init_options.Pin = (uint32_t)pin;
		gpio_init_options.Mode = (uint32_t)options._mode;
		gpio_init_options.Pull = (uint32_t)options._pull_mode;
		gpio_init_options.Speed = (uint32_t)options._speed;
		HAL_GPIO_Init(port_addr, &gpio_init_options);
	}
};

GpioPort &g_gpio_port_a = GpioPortA::Instance();
#endif // GPIOA

#ifdef GPIOB
class GpioPortB :public GpioPort
{
public:
	GpioPortB()
	{
		port_addr = GPIOB;
	}

	static GpioPortB &Instance()
	{
		static GpioPortB port{};
		return port;
	}

public:
	bool IsClockEnabled() override
	{
		return __HAL_RCC_GPIOB_IS_CLK_ENABLED();
	}

	void EnableClock() override
	{
		__HAL_RCC_GPIOB_CLK_ENABLE();
	}

	void DisableClock() override
	{
		__HAL_RCC_GPIOB_CLK_DISABLE();
	}

	void InitPin(GpioPin pin, GpioPinOptions const &options) override
	{
		GPIO_InitTypeDef gpio_init_options;
		gpio_init_options.Pin = (uint32_t)pin;
		gpio_init_options.Mode = (uint32_t)options._mode;
		gpio_init_options.Pull = (uint32_t)options._pull_mode;
		gpio_init_options.Speed = (uint32_t)options._speed;
		HAL_GPIO_Init(port_addr, &gpio_init_options);
	}
};

GpioPort &g_gpio_port_b = GpioPortB::Instance();
#endif // GPIOB

#ifdef GPIOE
class GpioPortE :public GpioPort
{
public:
	GpioPortE()
	{
		port_addr = GPIOE;
	}

	static GpioPortE &Instance()
	{
		static GpioPortE port{};
		return port;
	}

public:
	bool IsClockEnabled() override
	{
		return __HAL_RCC_GPIOE_IS_CLK_ENABLED();
	}

	void EnableClock() override
	{
		__HAL_RCC_GPIOE_CLK_ENABLE();
	}

	void DisableClock() override
	{
		__HAL_RCC_GPIOE_CLK_DISABLE();
	}

	void InitPin(GpioPin pin, GpioPinOptions const &options) override
	{
		GPIO_InitTypeDef gpio_init_options;
		gpio_init_options.Pin = (uint32_t)pin;
		gpio_init_options.Mode = (uint32_t)options._mode;
		gpio_init_options.Pull = (uint32_t)options._pull_mode;
		gpio_init_options.Speed = (uint32_t)options._speed;
		HAL_GPIO_Init(port_addr, &gpio_init_options);
	}
};

GpioPort &g_gpio_port_e = GpioPortE::Instance();
#endif // GPIOE
