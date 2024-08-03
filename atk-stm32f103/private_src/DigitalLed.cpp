#include "DigitalLed.h"
#include <base/Initializer.h>

using namespace bsp;
using namespace hal;

static base::Initializer _initializer{
	[]()
	{
		RedDigitalLed::Instance();
		GreenDigitalLed::Instance();
	}};

#pragma region RedDigitalLed
bsp::RedDigitalLed::RedDigitalLed()
{
	_pin = DI_GpioPinCollection().Get("PB5");
	if (_pin == nullptr)
	{
		throw std::runtime_error{"无法找到 PB5 引脚"};
	}

	std::shared_ptr<bsp::IGpioPinOptions> options = DICreate_GpioPinOptions();
	options->SetWorkMode(bsp::IGpioPinWorkMode::Gpio);
	options->SetDirection(bsp::IGpioPinDirection::Output);
	options->SetDriver(bsp::IGpioPinDriver::PushPull);
	options->SetPullMode(bsp::IGpioPinPullMode::PullUp);
	options->SetSpeedLevel(2);
	_pin->Open(*options);
}

void bsp::RedDigitalLed::TurnOn()
{
	// GPIO 引脚连接着 LED 的阴极，所以写 0 是打开
	GpioPortB::Instance().DigitalWritePin(hal::GpioPinConfig::PinEnum::Pin5, 0);
}

void bsp::RedDigitalLed::TurnOff()
{
	// GPIO 引脚连接着 LED 的阴极，所以写 1 是关闭。
	GpioPortB::Instance().DigitalWritePin(hal::GpioPinConfig::PinEnum::Pin5, 1);
}

void bsp::RedDigitalLed::Toggle()
{
	GpioPortB::Instance().DigitalTogglePin(hal::GpioPinConfig::PinEnum::Pin5);
}
#pragma endregion

#pragma region GreenDigitalLed
bsp::GreenDigitalLed::GreenDigitalLed()
{
	using namespace hal;
	GpioPortE::Instance().EnableClock();
	GpioPinConfig gpio_pin_options;
	gpio_pin_options.SetPin(hal::GpioPinConfig::PinEnum::Pin5);
	gpio_pin_options.SetMode(hal::GpioPinConfig::ModeOption::Output_PushPull);
	gpio_pin_options.SetPull(hal::GpioPinConfig::PullOption::PullUp);
	gpio_pin_options.SetSpeed(hal::GpioPinConfig::SpeedOption::High);
	GpioPortE::Instance().InitPin(gpio_pin_options);
}

void bsp::GreenDigitalLed::TurnOn()
{
	// GPIO 引脚连接着 LED 的阴极，所以写 0 是打开
	GpioPortE::Instance().DigitalWritePin(hal::GpioPinConfig::PinEnum::Pin5, 0);
}

void bsp::GreenDigitalLed::TurnOff()
{
	// GPIO 引脚连接着 LED 的阴极，所以写 1 是关闭。
	GpioPortE::Instance().DigitalWritePin(hal::GpioPinConfig::PinEnum::Pin5, 1);
}

void bsp::GreenDigitalLed::Toggle()
{
	GpioPortE::Instance().DigitalTogglePin(hal::GpioPinConfig::PinEnum::Pin5);
}
#pragma endregion
