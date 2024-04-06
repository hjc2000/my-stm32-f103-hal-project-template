#pragma once
// 这个头文件要最先包含，所以放到双引号里，避免 vs 的头文件排序把它放到后面去
#include"stm32f1xx_hal.h"
#include<GpioPort.h>
#include<stdint.h>
#include<stm32f1xx_hal_def.h>

class GpioPortA :public GpioPort
{
public:
	// 通过 GpioPort 继承
	bool IsClockEnabled() override;

	void EnableClock() override;

	void DisableClock() override;

};

extern GpioPortA g_gpio_port_a;