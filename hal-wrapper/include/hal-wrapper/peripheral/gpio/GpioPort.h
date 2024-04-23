#pragma once
#include<hal-wrapper/IClockSwitchable.h>
#include<hal-wrapper/IHardwareInstanceWrapper.h>
#include<hal-wrapper/peripheral/gpio/GpioPinInitOptions.h>
#include<hal.h>

namespace hal
{
	/// <summary>
	///		GPIO 端口抽象类，有几组 GPIO 端口就派生几个本类。
	/// </summary>
	class GpioPort :
		public IHardwareInstanceWrapper<GPIO_TypeDef>,
		public IClockSwitchable
	{
	public:
		void InitPin(GpioPin pin, GpioPinInitOptions const &options);
		void DigitalWritePin(GpioPin pin, bool value);
		bool DigitalReadPin(GpioPin pin);
		void DigitalTogglePin(GpioPin pin);
	};

	#pragma region GpioPortA
	#ifdef GPIOA
	class GpioPortA :public GpioPort
	{
	public:
		static GpioPortA &Instance()
		{
			static GpioPortA port{};
			return port;
		}

		GPIO_TypeDef *HardwareInstance() override;
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
		static GpioPortB &Instance()
		{
			static GpioPortB port{};
			return port;
		}

		GPIO_TypeDef *HardwareInstance() override;
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
		static GpioPortC &Instance()
		{
			static GpioPortC port{};
			return port;
		}

		GPIO_TypeDef *HardwareInstance() override;
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
		static GpioPortD &Instance()
		{
			static GpioPortD port{};
			return port;
		}

		GPIO_TypeDef *HardwareInstance() override;
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
		static GpioPortE &Instance()
		{
			static GpioPortE port{};
			return port;
		}

		GPIO_TypeDef *HardwareInstance() override;
		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;
	};
	#endif // GPIOE
	#pragma endregion
}
