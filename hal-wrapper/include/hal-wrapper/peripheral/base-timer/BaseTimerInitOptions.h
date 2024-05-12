#pragma once
#include<hal.h>

namespace hal
{
	class BaseTimerInitOptions
	{
	public:
		BaseTimerInitOptions() = default;
		BaseTimerInitOptions(TIM_Base_InitTypeDef const &o);
		BaseTimerInitOptions &operator=(TIM_Base_InitTypeDef const &o);
		operator TIM_Base_InitTypeDef();

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

		CounterMode _counter_mode;

		/// <summary>
		///		范围：[0x0000, 0xFFFF]
		/// </summary>
		uint32_t _period;

		enum class ClockDivision
		{
			Div1 = TIM_CLOCKDIVISION_DIV1,
			Div2 = TIM_CLOCKDIVISION_DIV2,
			Div4 = TIM_CLOCKDIVISION_DIV4,
		};

		ClockDivision _clock_division;

		uint32_t _repetition_counter;

		enum class AutoReloadPreload
		{
			Enable = TIM_AUTORELOAD_PRELOAD_ENABLE,
			Disable = TIM_AUTORELOAD_PRELOAD_DISABLE,
		};

		AutoReloadPreload _auto_reload_preload;
	};
}
