#pragma once
#include<hal-wrapper/peripheral/gpio/IGpioPort.h>

namespace hal
{
	#pragma region GpioPortA
	#ifdef GPIOA
	class GpioPortA :public IGpioPort
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
	class GpioPortB :public IGpioPort
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
	class GpioPortC :public IGpioPort
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
	class GpioPortD :public IGpioPort
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
	class GpioPortE :public IGpioPort
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
