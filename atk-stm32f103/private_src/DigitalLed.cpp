#include "DigitalLed.h"

using namespace bsp;

#pragma region RedDigitalLed

bsp::RedDigitalLed::RedDigitalLed()
{
    _pin = DI_GpioPinCollection().Get("PB5");
    _pin->OpenAsOutputMode(bsp::IGpioPinPullMode::NoPull, bsp::IGpioPinDriver::PushPull);
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
    _pin->OpenAsOutputMode(bsp::IGpioPinPullMode::NoPull, bsp::IGpioPinDriver::PushPull);
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
