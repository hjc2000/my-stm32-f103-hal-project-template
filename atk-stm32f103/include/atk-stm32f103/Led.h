#pragma once
#include<hal-wrapper/GpioPort.h>
#include<hal-wrapper/device/Led.h>

namespace atk
{
	class RedDigitalLed :public hal::DigitalLed
	{
	public:
		static RedDigitalLed &Instance()
		{
			static RedDigitalLed led;
			return led;
		}

	public:
		void Initialize() override;
		void Deinitialize() override;

		void TurnOn() override;
		void TurnOff() override;
		void Toggle() override;
	};

	class GreenDigitalLed :public hal::DigitalLed
	{
	public:
		static GreenDigitalLed &Instance()
		{
			static GreenDigitalLed led;
			return led;
		}

	public:
		void Initialize() override;
		void Deinitialize() override;

		void TurnOn() override;
		void TurnOff() override;
		void Toggle() override;
	};
}