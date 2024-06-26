#pragma once
#include<bsp-interface/IDigitalLed.h>
#include<hal-wrapper/peripheral/gpio/GpioPort.h>

namespace bsp
{
	/// <summary>
	///		红色 LED
	/// </summary>
	class RedDigitalLed :public bsp::IDigitalLed
	{
	public:
		RedDigitalLed()
		{
			using namespace hal;
			hal::GpioPortB::Instance().EnableClock();

			/* 使能时钟后写输出寄存器的操作就有效了。先关闭 LED，然后配置为输出模式，
			* 这样 LED 的初始状态就是关闭的。
			*/
			TurnOff();
			GpioPinConfig gpio_pin_options;
			gpio_pin_options.SetPin(hal::GpioPinConfig::PinEnum::Pin5);
			gpio_pin_options.SetMode(hal::GpioPinConfig::ModeOption::Output_PushPull);
			gpio_pin_options.SetPull(hal::GpioPinConfig::PullOption::PullUp);
			gpio_pin_options.SetSpeed(hal::GpioPinConfig::SpeedOption::High);
			GpioPortB::Instance().InitPin(gpio_pin_options);
		}

		static RedDigitalLed &Instance()
		{
			static RedDigitalLed led;
			return led;
		}

		void TurnOn() override;
		void TurnOff() override;
		void Toggle() override;
	};

	/// <summary>
	///		绿色 LED
	/// </summary>
	class GreenDigitalLed :public bsp::IDigitalLed
	{
	public:
		GreenDigitalLed()
		{
			using namespace hal;
			GpioPortE::Instance().EnableClock();

			/* 使能时钟后写输出寄存器的操作就有效了。先关闭 LED，然后配置为输出模式，
			* 这样 LED 的初始状态就是关闭的。
			*/
			TurnOff();
			GpioPinConfig gpio_pin_options;
			gpio_pin_options.SetPin(hal::GpioPinConfig::PinEnum::Pin5);
			gpio_pin_options.SetMode(hal::GpioPinConfig::ModeOption::Output_PushPull);
			gpio_pin_options.SetPull(hal::GpioPinConfig::PullOption::PullUp);
			gpio_pin_options.SetSpeed(hal::GpioPinConfig::SpeedOption::High);
			GpioPortE::Instance().InitPin(gpio_pin_options);
		}

		static GreenDigitalLed &Instance()
		{
			static GreenDigitalLed led;
			return led;
		}

		void TurnOn() override;
		void TurnOff() override;
		void Toggle() override;
	};
}
