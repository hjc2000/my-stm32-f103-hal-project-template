#pragma once
#include<hal-wrapper/clock/clock-signal/ClockSignalEnum.h>

namespace hal
{
	class ClockSignalInitOptions
	{
	public:
		ClockSignalInitOptions() = default;
		ClockSignalInitOptions(RCC_ClkInitTypeDef const &def);
		ClockSignalInitOptions &operator=(RCC_ClkInitTypeDef const &def);

		ClockType _clock_type;
		SysclkSource _sysclk_source;

		/// <summary>
		///		AHB 分频器。分频后输出 HCLK。
		/// </summary>
		AHBDivider _ahb_clk_divider;

		/// <summary>
		///		APB1 分频器的分频系数。分频后输出 PCLK1，此即低速外设时钟。
		/// </summary>
		APBDivider _apb1_divider;

		/// <summary>
		///		APB2 分频器的分频系数。分频后输出 PCLK2，此即高速外设时钟。
		/// </summary>
		APBDivider _apb2_divider;

		operator RCC_ClkInitTypeDef() const;
	};
}