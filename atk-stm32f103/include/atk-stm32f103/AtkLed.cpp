#include"AtkLed.h"

using namespace hal;
using namespace atk;

#pragma region RedDigitalLed
void atk::RedDigitalLed::Initialize()
{
	GpioPortB::Instance().EnableClock();

	/* 使能时钟后写输出寄存器的操作就有效了。先关闭 LED，然后配置为输出模式，
	* 这样 LED 的初始状态就是关闭的。
	*/
	TurnOff();
	GpioPinInitOptions gpio_pin_options;
	gpio_pin_options._mode = GpioPinMode::Output_PushPull;
	gpio_pin_options._pull_mode = GpioPinPull::PullUp;
	gpio_pin_options._speed = GpioPinSpeed::High;
	GpioPortB::Instance().InitPin(GpioPin::Pin5, gpio_pin_options);
}

void atk::RedDigitalLed::Deinitialize()
{
	/* 反初始化时不能将 GPIOB 的时钟给禁用了，因为该端口可能还有其他引脚需要使用。*/
	GpioPinInitOptions gpio_pin_options;
	gpio_pin_options._mode = GpioPinMode::Input;
	gpio_pin_options._pull_mode = GpioPinPull::NoPull;
	gpio_pin_options._speed = GpioPinSpeed::High;
	GpioPortB::Instance().InitPin(GpioPin::Pin5, gpio_pin_options);
}

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
void atk::GreenDigitalLed::Initialize()
{
	GpioPortE::Instance().EnableClock();

	/* 使能时钟后写输出寄存器的操作就有效了。先关闭 LED，然后配置为输出模式，
	* 这样 LED 的初始状态就是关闭的。
	*/
	TurnOff();
	GpioPinInitOptions gpio_pin_options;
	gpio_pin_options._mode = GpioPinMode::Output_PushPull;
	gpio_pin_options._pull_mode = GpioPinPull::PullUp;
	gpio_pin_options._speed = GpioPinSpeed::High;
	GpioPortE::Instance().InitPin(GpioPin::Pin5, gpio_pin_options);
}

void atk::GreenDigitalLed::Deinitialize()
{
	/* 反初始化时不能将 GPIOB 的时钟给禁用了，因为该端口可能还有其他引脚需要使用。*/
	GpioPinInitOptions gpio_pin_options;
	gpio_pin_options._mode = GpioPinMode::Input;
	gpio_pin_options._pull_mode = GpioPinPull::NoPull;
	gpio_pin_options._speed = GpioPinSpeed::High;
	GpioPortE::Instance().InitPin(GpioPin::Pin5, gpio_pin_options);
}

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
