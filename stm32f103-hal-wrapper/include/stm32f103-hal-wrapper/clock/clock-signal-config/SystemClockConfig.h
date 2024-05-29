#pragma once
#include<stm32f103-hal-wrapper/clock/clock-signal-config/AhbClkConfig.h>

namespace hal
{
	class SystemClockConfig
	{
	public:
		enum class ClockSource
		{
			HSI = RCC_SYSCLKSOURCE_HSI,
			HSE = RCC_SYSCLKSOURCE_HSE,
			PLLCLK = RCC_SYSCLKSOURCE_PLLCLK,
		};

		/// <summary>
		///		选择 SYSCLK 的时钟源
		/// </summary>
		ClockSource _clock_source = ClockSource::PLLCLK;

		AhbClkConfig _ahb_clk_config;

		void Serialize(RCC_ClkInitTypeDef &o) const;
		void Deserialize(RCC_ClkInitTypeDef const &o);
	};
}
