#pragma once
#include<hal.h>

namespace hal
{
	/// <summary>
	///		看门狗预分频器分频系数
	/// </summary>
	enum class WatchDogPrescaler
	{
		Div4 = IWDG_PRESCALER_4,
		Div8 = IWDG_PRESCALER_8,
		Div16 = IWDG_PRESCALER_16,
		Div32 = IWDG_PRESCALER_32,
		Div64 = IWDG_PRESCALER_64,
		Div128 = IWDG_PRESCALER_128,
		Div256 = IWDG_PRESCALER_256,
	};

	/// <summary>
	///		看门狗初始化选项。
	/// </summary>
	class WatchDogInitOptions
	{
	public:
		WatchDogInitOptions() = default;
		WatchDogInitOptions(WatchDogInitOptions const &o) = default;
		WatchDogInitOptions(IWDG_InitTypeDef const &o);
		WatchDogInitOptions &operator=(IWDG_InitTypeDef const &o);
		WatchDogInitOptions &operator=(WatchDogInitOptions const &o) = default;

		/// <summary>
		///		看门狗预分频器分频系数。
		/// </summary>
		WatchDogPrescaler _prescaler;

		/// <summary>
		///		看门狗重载值。范围：[0, 0x0FFF]
		/// </summary>
		uint32_t _reload;

		operator IWDG_InitTypeDef() const;
	};
}
