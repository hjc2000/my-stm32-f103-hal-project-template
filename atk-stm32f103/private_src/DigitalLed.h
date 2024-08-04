#pragma once
#include <bsp-interface/IDigitalLed.h>
#include <bsp-interface/di.h>
#include <gpio/GpioPinOptions.h>
#include <gpio/GpioPinPB5.h>
#include <gpio/GpioPinPE5.h>
#include <hal-wrapper/peripheral/gpio/GpioPort.h>

namespace bsp
{
	/// @brief 红色 LED
	class RedDigitalLed
		: public bsp::IDigitalLed
	{
	private:
		RedDigitalLed();

		bsp::IGpioPin *_pin = nullptr;

	public:
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
	class GreenDigitalLed
		: public bsp::IDigitalLed
	{
	private:
		GreenDigitalLed();

		bsp::IGpioPin *_pin = nullptr;

	public:
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
