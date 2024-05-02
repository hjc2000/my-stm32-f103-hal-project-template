#pragma once
#include<Delayer.h>
#include<bsp-interface/IKey.h>
#include<hal-wrapper/peripheral/gpio/GpioPort.h>

namespace atk
{
	/// <summary>
	///		位于 PE4 引脚上的按键。另一端接地，所以要上拉使用。
	/// </summary>
	class Key0 :public bsp::IKey
	{
	public:
		Key0();

		static Key0 &Instance()
		{
			static Key0 key{};
			return key;
		}

		hal::IGpioPort &Port()
		{
			return hal::GpioPortE::Instance();
		}

		bool KeyIsDown() override;

		void Delay(std::chrono::milliseconds num) override
		{
			hal::Delayer::Instance().Delay(num);
		}
	};

	/// <summary>
	///		位于 PE3 引脚。另一端接地，所以需要上拉使用。
	/// </summary>
	class Key1 :public bsp::IKey
	{
	public:
		Key1();

		static Key1 &Instance()
		{
			static Key1 key{};
			return key;
		}

		hal::IGpioPort &Port()
		{
			return hal::GpioPortE::Instance();
		}

		bool KeyIsDown() override;

		void Delay(std::chrono::milliseconds num) override
		{
			hal::Delayer::Instance().Delay(num);
		}
	};

	/// <summary>
	///		位于 PA0 引脚。另一端接 VCC，所以需要下拉使用。
	/// </summary>
	class KeyWakeUp :public bsp::IKey
	{
	public:
		KeyWakeUp();

		static KeyWakeUp &Instance()
		{
			static KeyWakeUp key{};
			return key;
		}

		hal::IGpioPort &Port()
		{
			return hal::GpioPortA::Instance();
		}

		bool KeyIsDown() override;

		void Delay(std::chrono::milliseconds num) override
		{
			hal::Delayer::Instance().Delay(num);
		}
	};
}
