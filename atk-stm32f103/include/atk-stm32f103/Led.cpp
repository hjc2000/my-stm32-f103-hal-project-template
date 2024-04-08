#include<atk-stm32f103/Led.h>

using namespace hal;
using namespace atk;

#pragma region RedDigitalLed
void atk::RedDigitalLed::Initialize()
{
	GpioPortB::Instance().EnableClock();
	GpioPinOptions gpio_pin_options;
	gpio_pin_options._mode = GpioPinMode::Output_PushPull;
	gpio_pin_options._pull_mode = GpioPinPull::PullUp;
	gpio_pin_options._speed = GpioPinSpeed::High;
	GpioPortB::Instance().InitPin(GpioPin::Pin5, gpio_pin_options);
}

void atk::RedDigitalLed::Deinitialize()
{
	/* 反初始化时不能将 GPIOB 的时钟给禁用了，因为该端口可能还有其他引脚需要使用。*/
	GpioPinOptions gpio_pin_options;
	gpio_pin_options._mode = GpioPinMode::Input;
	gpio_pin_options._pull_mode = GpioPinPull::NoPull;
	gpio_pin_options._speed = GpioPinSpeed::High;
	GpioPortB::Instance().InitPin(GpioPin::Pin5, gpio_pin_options);
}

void atk::RedDigitalLed::SwitchOn()
{
	// GPIO 引脚连接着 LED 的阴极，所以写 0 是打开
	GpioPortB::Instance().DigitalWritePin(GpioPin::Pin5, 0);
}

void atk::RedDigitalLed::SwitchOff()
{
	// GPIO 引脚连接着 LED 的阴极，所以写 1 是关闭。
	GpioPortB::Instance().DigitalWritePin(GpioPin::Pin5, 1);
}
#pragma endregion

#pragma region GreenDigitalLed
void atk::GreenDigitalLed::Initialize()
{
	GpioPortE::Instance().EnableClock();
	GpioPinOptions gpio_pin_options;
	gpio_pin_options._mode = GpioPinMode::Output_PushPull;
	gpio_pin_options._pull_mode = GpioPinPull::PullUp;
	gpio_pin_options._speed = GpioPinSpeed::High;
	GpioPortE::Instance().InitPin(GpioPin::Pin5, gpio_pin_options);
}

void atk::GreenDigitalLed::Deinitialize()
{
	/* 反初始化时不能将 GPIOB 的时钟给禁用了，因为该端口可能还有其他引脚需要使用。*/
	GpioPinOptions gpio_pin_options;
	gpio_pin_options._mode = GpioPinMode::Input;
	gpio_pin_options._pull_mode = GpioPinPull::NoPull;
	gpio_pin_options._speed = GpioPinSpeed::High;
	GpioPortE::Instance().InitPin(GpioPin::Pin5, gpio_pin_options);
}

void atk::GreenDigitalLed::SwitchOn()
{
	// GPIO 引脚连接着 LED 的阴极，所以写 0 是打开
	GpioPortE::Instance().DigitalWritePin(GpioPin::Pin5, 0);
}

void atk::GreenDigitalLed::SwitchOff()
{
	// GPIO 引脚连接着 LED 的阴极，所以写 1 是关闭。
	GpioPortE::Instance().DigitalWritePin(GpioPin::Pin5, 1);
}
#pragma endregion
