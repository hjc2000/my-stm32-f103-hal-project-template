#pragma once
// 这个头文件要最先包含，所以放到双引号里，避免 vs 的头文件排序把它放到后面去
#include"stm32f1xx_hal.h"
#include<stdint.h>
#include<stm32f1xx_hal_def.h>
#include<stm32f1xx_hal_gpio.h>

/// <summary>
///		定义 GPIO 引脚。
/// </summary>
enum class GpioPin : uint16_t
{
	Pin0 = GPIO_PIN_0,
	Pin1 = GPIO_PIN_1,
	Pin2 = GPIO_PIN_2,
	Pin3 = GPIO_PIN_3,
	Pin4 = GPIO_PIN_4,
	Pin5 = GPIO_PIN_5,
	Pin6 = GPIO_PIN_6,
	Pin7 = GPIO_PIN_7,
	Pin8 = GPIO_PIN_8,
	Pin9 = GPIO_PIN_9,
	Pin10 = GPIO_PIN_10,
	Pin11 = GPIO_PIN_11,
	Pin12 = GPIO_PIN_12,
	Pin13 = GPIO_PIN_13,
	Pin14 = GPIO_PIN_14,
	Pin15 = GPIO_PIN_15,
};

/// <summary>
///		定义 GPIO 引脚模式。
/// </summary>
enum class GpioPinMode :uint32_t
{
	Input = GPIO_MODE_INPUT,

	Output_PushPull = GPIO_MODE_OUTPUT_PP,
	Output_OpenDrain = GPIO_MODE_OUTPUT_OD,

	AlternateFunction_PushPull = GPIO_MODE_AF_PP,
	AlternateFunction_OpenDrain = GPIO_MODE_AF_OD,
	AlternateFunction_Input = GPIO_MODE_AF_INPUT,

	Analog = GPIO_MODE_ANALOG,

	Interrupt_RisingEdgeTrigger = GPIO_MODE_IT_RISING,
	Interrupt_FallingEdgeTrigger = GPIO_MODE_IT_FALLING,
	Interrupt_BothEdgeTrigger = GPIO_MODE_IT_RISING_FALLING,

	Event_RisingEdgeTrigger = GPIO_MODE_EVT_RISING,
	Event_FallingEdgeTrigger = GPIO_MODE_EVT_FALLING,
	Event_BothEdgeTrigger = GPIO_MODE_EVT_RISING_FALLING,
};

/// <summary>
///		定义 GPIO 引脚的上下拉模式。
/// </summary>
enum class GpioPinPull :uint32_t
{
	NoPull = GPIO_NOPULL,
	PullUp = GPIO_PULLUP,
	PullDown = GPIO_PULLDOWN,
};

/// <summary>
///		定义 GPIO 引脚的最大速度。
/// </summary>
enum GpioPinSpeed :uint32_t
{
	Low = GPIO_SPEED_FREQ_LOW,
	Medium = GPIO_SPEED_FREQ_MEDIUM,
	High = GPIO_SPEED_FREQ_HIGH,
};

struct GpioPinOptions
{
	GpioPinMode mode = GpioPinMode::Input;
	GpioPinPull pull_mode = GpioPinPull::NoPull;
	GpioPinSpeed speed = GpioPinSpeed::High;
};

/// <summary>
///		GPIO 端口抽象类，有几组 GPIO 端口就派生几个本类。
/// </summary>
class GpioPort
{
public:
	virtual bool IsClockEnabled() = 0;
	bool IsClockDisabled();

	virtual void EnableClock() = 0;
	virtual void DisableClock() = 0;

	virtual void InitPin(GpioPin pin, GpioPinOptions const &options) = 0;
	virtual void DigitalWritePin(GpioPin pin, bool value) = 0;
};
