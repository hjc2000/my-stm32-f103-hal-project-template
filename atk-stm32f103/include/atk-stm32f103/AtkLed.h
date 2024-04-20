#pragma once
#include<hal-wrapper/device/IDigitalLed.h>
#include<hal-wrapper/peripheral/GpioPort.h>

namespace atk
{
	/// <summary>
	///		红色 LED
	/// </summary>
	class RedDigitalLed :public hal::IDigitalLed
	{
	public:
		static RedDigitalLed &Instance()
		{
			static RedDigitalLed led;
			return led;
		}

	public:
		void Initialize();
		void Deinitialize();

		void TurnOn() override;
		void TurnOff() override;
		void Toggle() override;
	};

	/// <summary>
	///		绿色 LED
	/// </summary>
	class GreenDigitalLed :public hal::IDigitalLed
	{
	public:
		static GreenDigitalLed &Instance()
		{
			static GreenDigitalLed led;
			return led;
		}

	public:
		void Initialize();
		void Deinitialize();

		void TurnOn() override;
		void TurnOff() override;
		void Toggle() override;
	};
}