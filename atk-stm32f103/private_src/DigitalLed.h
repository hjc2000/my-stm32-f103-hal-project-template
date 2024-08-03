#pragma once
#include <bsp-interface/IDigitalLed.h>
#include <bsp-interface/di.h>
#include <hal-wrapper/peripheral/gpio/GpioPin.h>
#include <hal-wrapper/peripheral/gpio/GpioPinOptions.h>
#include <hal-wrapper/peripheral/gpio/GpioPort.h>

namespace bsp
{
	/// @brief 红色 LED
	class RedDigitalLed
		: public bsp::IDigitalLed
	{
	private:
		bsp::IGpioPin *_pin = nullptr;

	public:
		RedDigitalLed()
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

		static RedDigitalLed &Instance()
		{
			static RedDigitalLed led;
			return led;
		}

		void TurnOn() override;
		void TurnOff() override;
		void Toggle() override;
	};

	/// @brief 绿色 LED
	class GreenDigitalLed : public bsp::IDigitalLed
	{
	public:
		GreenDigitalLed()
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
