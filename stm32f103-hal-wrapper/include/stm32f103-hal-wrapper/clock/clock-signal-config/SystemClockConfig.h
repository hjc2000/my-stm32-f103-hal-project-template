#pragma once
#include<stm32f103-hal-wrapper/clock/clock-signal-config/AhbClkConfig.h>

namespace hal
{
	/// <summary>
	///		系统时钟配置。
	///		* 时钟源的输出端直接连着系统时钟，作为系统时钟的输入端。
	///		* 系统时钟可以选择多个时钟源。
	///		* 系统时钟是时钟信号的根。
	/// </summary>
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
