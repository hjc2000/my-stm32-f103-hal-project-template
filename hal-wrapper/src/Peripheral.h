#pragma once
#include<GpioPort.h>

#ifdef GPIOA
class GpioPortA :public GpioPort
{
public:
	GpioPortA()
	{
		port_addr = GPIOA;
	}

public:
	bool IsClockEnabled() override;
	void EnableClock() override;
	void DisableClock() override;

	void InitPin(GpioPin pin, GpioPinOptions const &options) override;
};

extern GpioPortA g_gpio_port_a;
#endif // GPIOA

#ifdef GPIOB
class GpioPortB :public GpioPort
{
public:
	GpioPortB()
	{
		port_addr = GPIOB;
	}

public:
	bool IsClockEnabled() override;
	void EnableClock() override;
	void DisableClock() override;

	void InitPin(GpioPin pin, GpioPinOptions const &options) override;
};

extern GpioPortB g_gpio_port_b;
#endif // GPIOB

#ifdef GPIOE
class GpioPortE :public GpioPort
{
public:
	GpioPortE()
	{
		port_addr = GPIOE;
	}

public:
	bool IsClockEnabled() override;
	void EnableClock() override;
	void DisableClock() override;

	void InitPin(GpioPin pin, GpioPinOptions const &options) override;
};

extern GpioPortE g_gpio_port_e;
#endif // GPIOE