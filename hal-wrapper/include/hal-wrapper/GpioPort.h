#pragma once
#include<hal.h>

namespace hal
{
	#pragma region GPIO相关的枚举
	/// <summary>
	///		定义 GPIO 引脚。
	/// </summary>
	enum class GpioPin : uint16_t
	{
		Pin0 = GPIO_PIN_0,
		Pin1 = GPIO_PIN_1,
		Pin2 = GPIO_PIN_2,
		Pin3 = GPIO_PIN_3,
		Pin4 = GPIO_PIN_4,
		Pin5 = GPIO_PIN_5,
		Pin6 = GPIO_PIN_6,
		Pin7 = GPIO_PIN_7,
		Pin8 = GPIO_PIN_8,
		Pin9 = GPIO_PIN_9,
		Pin10 = GPIO_PIN_10,
		Pin11 = GPIO_PIN_11,
		Pin12 = GPIO_PIN_12,
		Pin13 = GPIO_PIN_13,
		Pin14 = GPIO_PIN_14,
		Pin15 = GPIO_PIN_15,
	};

	/// <summary>
	///		定义 GPIO 引脚模式。
	/// </summary>
	enum class GpioPinMode :uint32_t
	{
		Input = GPIO_MODE_INPUT,

		Output_PushPull = GPIO_MODE_OUTPUT_PP,
		Output_OpenDrain = GPIO_MODE_OUTPUT_OD,

		AlternateFunction_PushPull = GPIO_MODE_AF_PP,
		AlternateFunction_OpenDrain = GPIO_MODE_AF_OD,
		AlternateFunction_Input = GPIO_MODE_AF_INPUT,

		Analog = GPIO_MODE_ANALOG,

		Interrupt_RisingEdgeTrigger = GPIO_MODE_IT_RISING,
		Interrupt_FallingEdgeTrigger = GPIO_MODE_IT_FALLING,
		Interrupt_BothEdgeTrigger = GPIO_MODE_IT_RISING_FALLING,

		Event_RisingEdgeTrigger = GPIO_MODE_EVT_RISING,
		Event_FallingEdgeTrigger = GPIO_MODE_EVT_FALLING,
		Event_BothEdgeTrigger = GPIO_MODE_EVT_RISING_FALLING,
	};

	/// <summary>
	///		定义 GPIO 引脚的上下拉模式。
	/// </summary>
	enum class GpioPinPull :uint32_t
	{
		NoPull = GPIO_NOPULL,
		PullUp = GPIO_PULLUP,
		PullDown = GPIO_PULLDOWN,
	};

	/// <summary>
	///		定义 GPIO 引脚的最大速度。
	/// </summary>
	enum GpioPinSpeed :uint32_t
	{
		Low = GPIO_SPEED_FREQ_LOW,
		Medium = GPIO_SPEED_FREQ_MEDIUM,
		High = GPIO_SPEED_FREQ_HIGH,
	};
	#pragma endregion

	struct GpioPinOptions
	{
		GpioPinMode _mode = GpioPinMode::Input;
		GpioPinPull _pull_mode = GpioPinPull::NoPull;
		GpioPinSpeed _speed = GpioPinSpeed::High;
	};

	/// <summary>
	///		GPIO 端口抽象类，有几组 GPIO 端口就派生几个本类。
	/// </summary>
	class GpioPort
	{
	protected:
		/// <summary>
		///		派生类需要在构造函数中为此字段赋值。
		/// </summary>
		GPIO_TypeDef *port_addr = nullptr;

	public:
		virtual bool IsClockEnabled() = 0;
		bool IsClockDisabled();

		virtual void EnableClock() = 0;
		virtual void DisableClock() = 0;

		void InitPin(GpioPin pin, GpioPinOptions const &options);
		void DigitalWritePin(GpioPin pin, bool value);
	};

	#pragma region GPIOA
	#ifdef GPIOA
	class GpioPortA :public GpioPort
	{
	public:
		GpioPortA()
		{
			port_addr = GPIOA;
		}

		static GpioPortA &Instance()
		{
			static GpioPortA port{};
			return port;
		}

	public:
		bool IsClockEnabled() override
		{
			return __HAL_RCC_GPIOA_IS_CLK_ENABLED();
		}

		void EnableClock() override
		{
			__HAL_RCC_GPIOA_CLK_ENABLE();
		}

		void DisableClock() override
		{
			__HAL_RCC_GPIOA_CLK_DISABLE();
		}
	};
	#endif // GPIOA
	#pragma endregion

	#pragma region GPIOB
	#ifdef GPIOB
	class GpioPortB :public GpioPort
	{
	public:
		GpioPortB()
		{
			port_addr = GPIOB;
		}

		static GpioPortB &Instance()
		{
			static GpioPortB port{};
			return port;
		}

	public:
		bool IsClockEnabled() override
		{
			return __HAL_RCC_GPIOB_IS_CLK_ENABLED();
		}

		void EnableClock() override
		{
			__HAL_RCC_GPIOB_CLK_ENABLE();
		}

		void DisableClock() override
		{
			__HAL_RCC_GPIOB_CLK_DISABLE();
		}
	};
	#endif // GPIOB
	#pragma endregion

	#pragma region GPIOC
	#ifdef GPIOC
	class GpioPortC :public GpioPort
	{
	public:
		GpioPortC()
		{
			port_addr = GPIOC;
		}

		static GpioPortC &Instance()
		{
			static GpioPortC port{};
			return port;
		}

	public:
		bool IsClockEnabled() override
		{
			return __HAL_RCC_GPIOC_IS_CLK_ENABLED();
		}

		void EnableClock() override
		{
			__HAL_RCC_GPIOC_CLK_ENABLE();
		}

		void DisableClock() override
		{
			__HAL_RCC_GPIOC_CLK_DISABLE();
		}
	};
	#endif // GPIOC
	#pragma endregion

	#pragma region GPIOD
	#ifdef GPIOD
	class GpioPortD :public GpioPort
	{
	public:
		GpioPortD()
		{
			port_addr = GPIOD;
		}

		static GpioPortD &Instance()
		{
			static GpioPortD port{};
			return port;
		}

	public:
		bool IsClockEnabled() override
		{
			return __HAL_RCC_GPIOD_IS_CLK_ENABLED();
		}

		void EnableClock() override
		{
			__HAL_RCC_GPIOD_CLK_ENABLE();
		}

		void DisableClock() override
		{
			__HAL_RCC_GPIOD_CLK_DISABLE();
		}
	};
	#endif // GPIOD
	#pragma endregion

	#pragma region GPIOE
	#ifdef GPIOE
	class GpioPortE :public GpioPort
	{
	public:
		GpioPortE()
		{
			port_addr = GPIOE;
		}

		static GpioPortE &Instance()
		{
			static GpioPortE port{};
			return port;
		}

	public:
		bool IsClockEnabled() override
		{
			return __HAL_RCC_GPIOE_IS_CLK_ENABLED();
		}

		void EnableClock() override
		{
			__HAL_RCC_GPIOE_CLK_ENABLE();
		}

		void DisableClock() override
		{
			__HAL_RCC_GPIOE_CLK_DISABLE();
		}
	};
	#endif // GPIOE
	#pragma endregion
}
