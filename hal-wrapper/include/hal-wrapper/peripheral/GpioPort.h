#pragma once
#include<hal-wrapper/peripheral/GpioEnum.h>
#include<hal-wrapper/peripheral/IPeripheral.h>
#include<hal.h>

namespace hal
{
	struct GpioPinOptions
	{
		GpioPinMode _mode = GpioPinMode::Input;
		GpioPinPull _pull_mode = GpioPinPull::NoPull;
		GpioPinSpeed _speed = GpioPinSpeed::High;
	};

	/// <summary>
	///		GPIO 端口抽象类，有几组 GPIO 端口就派生几个本类。
	/// </summary>
	class GpioPort :public IPeripheral
	{
	protected:
		/// <summary>
		///		派生类需要在构造函数中为此字段赋值。
		/// </summary>
		GPIO_TypeDef *_port_addr = nullptr;

	public:
		void InitPin(GpioPin pin, GpioPinOptions const &options);
		void DigitalWritePin(GpioPin pin, bool value);
		bool DigitalReadPin(GpioPin pin);
		void DigitalTogglePin(GpioPin pin);
	};

	#pragma region GpioPortA
	#ifdef GPIOA
	class GpioPortA :public GpioPort
	{
	public:
		GpioPortA()
		{
			_port_addr = GPIOA;
		}

		static GpioPortA &Instance()
		{
			static GpioPortA port{};
			return port;
		}

		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;
	};
	#endif // GPIOA
	#pragma endregion

	#pragma region GpioPortB
	#ifdef GPIOB
	class GpioPortB :public GpioPort
	{
	public:
		GpioPortB()
		{
			_port_addr = GPIOB;
		}

		static GpioPortB &Instance()
		{
			static GpioPortB port{};
			return port;
		}

		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;
	};
	#endif // GPIOB
	#pragma endregion

	#pragma region GpioPortC
	#ifdef GPIOC
	class GpioPortC :public GpioPort
	{
	public:
		GpioPortC()
		{
			_port_addr = GPIOC;
		}

		static GpioPortC &Instance()
		{
			static GpioPortC port{};
			return port;
		}

		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;
	};
	#endif // GPIOC
	#pragma endregion

	#pragma region GpioPortD
	#ifdef GPIOD
	class GpioPortD :public GpioPort
	{
	public:
		GpioPortD()
		{
			_port_addr = GPIOD;
		}

		static GpioPortD &Instance()
		{
			static GpioPortD port{};
			return port;
		}

		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;
	};
	#endif // GPIOD
	#pragma endregion

	#pragma region GpioPortE
	#ifdef GPIOE
	class GpioPortE :public GpioPort
	{
	public:
		GpioPortE()
		{
			_port_addr = GPIOE;
		}

		static GpioPortE &Instance()
		{
			static GpioPortE port{};
			return port;
		}

		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;
	};
	#endif // GPIOE
	#pragma endregion
}
