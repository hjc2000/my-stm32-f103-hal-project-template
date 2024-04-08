#include"hal-wrapper/GpioPort.h"

bool GpioPort::IsClockDisabled()
{
	return !IsClockEnabled();
}

void GpioPort::InitPin(GpioPin pin, GpioPinOptions const &options)
{
	GPIO_InitTypeDef gpio_init_options;
	gpio_init_options.Pin = (uint32_t)pin;
	gpio_init_options.Mode = (uint32_t)options._mode;
	gpio_init_options.Pull = (uint32_t)options._pull_mode;
	gpio_init_options.Speed = (uint32_t)options._speed;
	HAL_GPIO_Init(port_addr, &gpio_init_options);
}

void GpioPort::DigitalWritePin(GpioPin pin, bool value)
{
	GPIO_PinState state = value ? GPIO_PinState::GPIO_PIN_SET : GPIO_PinState::GPIO_PIN_RESET;
	HAL_GPIO_WritePin(port_addr, (uint16_t)pin, state);
}

#pragma region GPIOA
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
};

GpioPort &g_gpio_port_a = GpioPortA::Instance();
#endif // GPIOA
#pragma endregion

#pragma region GPIOB
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
};

GpioPort &g_gpio_port_b = GpioPortB::Instance();
#endif // GPIOB
#pragma endregion

#pragma region GPIOC
#ifdef GPIOC
class GpioPortC :public GpioPort
{
public:
	GpioPortC()
	{
		port_addr = GPIOC;
	}

	static GpioPortC &Instance()
	{
		static GpioPortC port{};
		return port;
	}

public:
	bool IsClockEnabled() override
	{
		return __HAL_RCC_GPIOC_IS_CLK_ENABLED();
	}

	void EnableClock() override
	{
		__HAL_RCC_GPIOC_CLK_ENABLE();
	}

	void DisableClock() override
	{
		__HAL_RCC_GPIOC_CLK_DISABLE();
	}
};

GpioPort &g_gpio_port_c = GpioPortC::Instance();
#endif // GPIOC
#pragma endregion

#pragma region GPIOD
#ifdef GPIOD
class GpioPortD :public GpioPort
{
public:
	GpioPortD()
	{
		port_addr = GPIOD;
	}

	static GpioPortD &Instance()
	{
		static GpioPortD port{};
		return port;
	}

public:
	bool IsClockEnabled() override
	{
		return __HAL_RCC_GPIOD_IS_CLK_ENABLED();
	}

	void EnableClock() override
	{
		__HAL_RCC_GPIOD_CLK_ENABLE();
	}

	void DisableClock() override
	{
		__HAL_RCC_GPIOD_CLK_DISABLE();
	}
};

GpioPort &g_gpio_port_d = GpioPortD::Instance();
#endif // GPIOD
#pragma endregion

#pragma region GPIOE
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
};

GpioPort &g_gpio_port_e = GpioPortE::Instance();
#endif // GPIOE
#pragma endregion
