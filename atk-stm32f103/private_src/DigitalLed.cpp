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
	options->SetPullMode(bsp::IGpioPinPullMode::NoPull);
	options->SetSpeedLevel(2);
	_pin->Open(*options);
	TurnOff();
}

void bsp::RedDigitalLed::TurnOn()
{
	// GPIO 引脚连接着 LED 的阴极，所以写 0 是打开
	_pin->WritePin(0);
}

void bsp::RedDigitalLed::TurnOff()
{
	// GPIO 引脚连接着 LED 的阴极，所以写 1 是关闭。
	_pin->WritePin(1);
}

void bsp::RedDigitalLed::Toggle()
{
	_pin->TogglePin();
}
#pragma endregion

#pragma region GreenDigitalLed
bsp::GreenDigitalLed::GreenDigitalLed()
{
	_pin = DI_GpioPinCollection().Get("PE5");
	if (_pin == nullptr)
	{
		throw std::runtime_error{"无法找到 PE5 引脚"};
	}

	std::shared_ptr<bsp::IGpioPinOptions> options = DICreate_GpioPinOptions();
	options->SetWorkMode(bsp::IGpioPinWorkMode::Gpio);
	options->SetDirection(bsp::IGpioPinDirection::Output);
	options->SetDriver(bsp::IGpioPinDriver::PushPull);
	options->SetPullMode(bsp::IGpioPinPullMode::NoPull);
	options->SetSpeedLevel(2);
	_pin->Open(*options);
	TurnOff();
}

void bsp::GreenDigitalLed::TurnOn()
{
	// GPIO 引脚连接着 LED 的阴极，所以写 0 是打开
	_pin->WritePin(0);
}

void bsp::GreenDigitalLed::TurnOff()
{
	// GPIO 引脚连接着 LED 的阴极，所以写 1 是关闭。
	_pin->WritePin(1);
}

void bsp::GreenDigitalLed::Toggle()
{
	_pin->TogglePin();
}
#pragma endregion
