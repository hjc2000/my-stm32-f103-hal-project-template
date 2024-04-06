#pragma once
// 这个头文件要最先包含，所以放到双引号里，避免 vs 的头文件排序把它放到后面去
#include<GpioPort.h>

class GpioPortA :public GpioPort
{
private:
	GPIO_TypeDef *port_addr = GPIOA;

public:
	bool IsClockEnabled() override;
	using GpioPort::IsClockDisabled;

	void EnableClock() override;
	void DisableClock() override;

	// 通过 GpioPort 继承
	void InitPin(GpioPin pin, GpioPinOptions const &options) override;

	// 通过 GpioPort 继承
	void WritePin(GpioPin pin, bool value) override;
};

extern GpioPortA g_gpio_port_a;



class GpioPortB :public GpioPort
{
private:
	GPIO_TypeDef *port_addr = GPIOB;

public:
	bool IsClockEnabled() override;
	using GpioPort::IsClockDisabled;

	void EnableClock() override;
	void DisableClock() override;

	// 通过 GpioPort 继承
	void InitPin(GpioPin pin, GpioPinOptions const &options) override;

	// 通过 GpioPort 继承
	void WritePin(GpioPin pin, bool value) override;
};

extern GpioPortB g_gpio_port_b;



class GpioPortE :public GpioPort
{
private:
	GPIO_TypeDef *port_addr = GPIOE;

public:
	bool IsClockEnabled() override;
	using GpioPort::IsClockDisabled;

	void EnableClock() override;
	void DisableClock() override;

	// 通过 GpioPort 继承
	void InitPin(GpioPin pin, GpioPinOptions const &options) override;

	// 通过 GpioPort 继承
	void WritePin(GpioPin pin, bool value) override;
};

extern GpioPortE g_gpio_port_e;
