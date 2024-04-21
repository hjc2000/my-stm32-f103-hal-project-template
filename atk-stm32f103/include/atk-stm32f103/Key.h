#pragma once
#include<hal-wrapper/device/IKey.h>
#include<hal-wrapper/peripheral/gpio/GpioPort.h>

namespace atk
{
	/// <summary>
	///		位于 PE4 引脚上的按键。另一端接地，所以要上拉使用。
	/// </summary>
	class Key0 :public hal::IKey
	{
	public:
		Key0()
		{
			using namespace hal;
			Port().EnableClock();
			GpioPinInitOptions options;
			options._mode = GpioPinMode::Input;
			options._pull_mode = GpioPinPull::PullUp;
			options._speed = GpioPinSpeed::High;
			Port().InitPin(GpioPin::Pin4, options);
		}

		static Key0 &Instance()
		{
			static Key0 key{};
			return key;
		}

		hal::GpioPort &Port()
		{
			return hal::GpioPortE::Instance();
		}

		bool KeyIsDown() override;
	};

	/// <summary>
	///		位于 PE3 引脚。另一端接地，所以需要上拉使用。
	/// </summary>
	class Key1 :public hal::IKey
	{
	public:
		Key1()
		{
			using namespace hal;
			Port().EnableClock();
			GpioPinInitOptions options;
			options._mode = GpioPinMode::Input;
			options._pull_mode = GpioPinPull::PullUp;
			options._speed = GpioPinSpeed::High;
			Port().InitPin(GpioPin::Pin3, options);
		}

		static Key1 &Instance()
		{
			static Key1 key{};
			return key;
		}

		hal::GpioPort &Port()
		{
			return hal::GpioPortE::Instance();
		}

		bool KeyIsDown() override;
	};

	/// <summary>
	///		位于 PA0 引脚。另一端接 VCC，所以需要下拉使用。
	/// </summary>
	class KeyWakeUp :public hal::IKey
	{
	public:
		KeyWakeUp()
		{
			using namespace hal;
			Port().EnableClock();
			GpioPinInitOptions options;
			options._mode = GpioPinMode::Input;
			options._pull_mode = GpioPinPull::PullDown;
			options._speed = GpioPinSpeed::High;
			Port().InitPin(GpioPin::Pin0, options);
		}

		static KeyWakeUp &Instance()
		{
			static KeyWakeUp key{};
			return key;
		}

		hal::GpioPort &Port()
		{
			return hal::GpioPortA::Instance();
		}

		bool KeyIsDown() override;
	};
}