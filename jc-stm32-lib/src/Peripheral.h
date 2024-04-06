#pragma once
// 这个头文件要最先包含，所以放到双引号里，避免 vs 的头文件排序把它放到后面去
#include<GpioPort.h>

class GpioPortA :public GpioPort
{
public:
	bool IsClockEnabled() override;
	using GpioPort::IsClockDisabled;

	void EnableClock() override;
	void DisableClock() override;

	// 通过 GpioPort 继承
	void InitPin(GpioPin pin, GpioPinOptions const &options) override;
};

extern GpioPortA g_gpio_port_a;



class GpioPortB :public GpioPort
{
public:
	bool IsClockEnabled() override;
	using GpioPort::IsClockDisabled;

	void EnableClock() override;
	void DisableClock() override;

	// 通过 GpioPort 继承
	void InitPin(GpioPin pin, GpioPinOptions const &options) override;
};

extern GpioPortB g_gpio_port_b;
