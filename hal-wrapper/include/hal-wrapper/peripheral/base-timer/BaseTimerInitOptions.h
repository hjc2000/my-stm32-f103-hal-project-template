#pragma once
#include<hal.h>

namespace hal
{
	class BaseTimerInitOptions
	{
	public:
		/// <summary>
		///		预分频器。范围：[0x0000, 0xFFFF]
		/// </summary>
		uint32_t _prescaler;

		enum class CounterMode
		{
			Up = TIM_COUNTERMODE_UP,
			Down = TIM_COUNTERMODE_DOWN,
			CenterAligned1 = TIM_COUNTERMODE_CENTERALIGNED1,
			CenterAligned2 = TIM_COUNTERMODE_CENTERALIGNED2,
			CenterAligned3 = TIM_COUNTERMODE_CENTERALIGNED3,
		};

		CounterMode _counter_mode;       /*!< Specifies the counter mode.
		This parameter can be a value of @ref TIM_Counter_Mode */

		/// <summary>
		///		计数片段。计数器从 0 计数到该值。范围：[0x0000, 0xFFFF]
		/// </summary>
		uint32_t _period;

		enum class ClockDivision
		{
			Div1 = TIM_CLOCKDIVISION_DIV1,
			Div2 = TIM_CLOCKDIVISION_DIV2,
			Div4 = TIM_CLOCKDIVISION_DIV4,
		};

		ClockDivision _clock_division;

		uint32_t RepetitionCounter;  /*!< Specifies the repetition counter value. Each time the RCR downcounter
		reaches zero, an update event is generated and counting restarts
		from the RCR value (N).
		This means in PWM mode that (N+1) corresponds to:
		- the number of PWM periods in edge-aligned mode
		- the number of half PWM period in center-aligned mode
		GP timers: this parameter must be a number between Min_Data = 0x00 and
		Max_Data = 0xFF.
		Advanced timers: this parameter must be a number between Min_Data = 0x0000 and
		Max_Data = 0xFFFF. */

		enum class AutoReloadPreload
		{
			Enable = TIM_AUTORELOAD_PRELOAD_ENABLE,
			Disable = TIM_AUTORELOAD_PRELOAD_DISABLE,
		};

		AutoReloadPreload _auto_reload_preload;
	};
}
