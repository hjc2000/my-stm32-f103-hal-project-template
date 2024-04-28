#include"DigitalLed.h"

using namespace hal;
using namespace atk;

#pragma region RedDigitalLed
void atk::RedDigitalLed::TurnOn()
{
	// GPIO 引脚连接着 LED 的阴极，所以写 0 是打开
	GpioPortB::Instance().DigitalWritePin(GpioPin::Pin5, 0);
}

void atk::RedDigitalLed::TurnOff()
{
	// GPIO 引脚连接着 LED 的阴极，所以写 1 是关闭。
	GpioPortB::Instance().DigitalWritePin(GpioPin::Pin5, 1);
}

void atk::RedDigitalLed::Toggle()
{
	GpioPortB::Instance().DigitalTogglePin(GpioPin::Pin5);
}
#pragma endregion

#pragma region GreenDigitalLed
void atk::GreenDigitalLed::TurnOn()
{
	// GPIO 引脚连接着 LED 的阴极，所以写 0 是打开
	GpioPortE::Instance().DigitalWritePin(GpioPin::Pin5, 0);
}

void atk::GreenDigitalLed::TurnOff()
{
	// GPIO 引脚连接着 LED 的阴极，所以写 1 是关闭。
	GpioPortE::Instance().DigitalWritePin(GpioPin::Pin5, 1);
}

void atk::GreenDigitalLed::Toggle()
{
	GpioPortE::Instance().DigitalTogglePin(GpioPin::Pin5);
}
#pragma endregion
