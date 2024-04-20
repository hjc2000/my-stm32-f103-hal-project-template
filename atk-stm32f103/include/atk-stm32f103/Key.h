#pragma once
#include<hal-wrapper/device/IKey.h>
#include<hal-wrapper/peripheral/GpioPort.h>

namespace atk
{
	/// <summary>
	///		位于 PE4 引脚上的按键。另一端接地，所以要上拉使用。
	/// </summary>
	class Key0 :public hal::IKey
	{
	public:
		static Key0 &Instance()
		{
			static Key0 key{};
			return key;
		}

	public:
		hal::GpioPort &Port()
		{
			return hal::GpioPortE::Instance();
		}

		void Initialize();
		void Deinitialize();
		bool KeyIsDown() override;
	};

	/// <summary>
	///		位于 PE3 引脚。另一端接地，所以需要上拉使用。
	/// </summary>
	class Key1 :public hal::IKey
	{
	public:
		static Key1 &Instance()
		{
			static Key1 key{};
			return key;
		}

	public:
		hal::GpioPort &Port()
		{
			return hal::GpioPortE::Instance();
		}

		void Initialize();
		void Deinitialize();
		bool KeyIsDown() override;
	};

	/// <summary>
	///		位于 PA0 引脚。另一端接 VCC，所以需要下拉使用。
	/// </summary>
	class KeyWakeUp :public hal::IKey
	{
	public:
		static KeyWakeUp &Instance()
		{
			static KeyWakeUp key{};
			return key;
		}

	public:
		hal::GpioPort &Port()
		{
			return hal::GpioPortA::Instance();
		}

		void Initialize();
		void Deinitialize();
		bool KeyIsDown() override;
	};
}