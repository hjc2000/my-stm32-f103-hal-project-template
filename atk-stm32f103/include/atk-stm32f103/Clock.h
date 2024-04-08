#pragma once
#include<hal-wrapper/Clock.h>
#include<hal-wrapper/Osc.h>

/// <summary>
///		将 HCLK 配置为 72MHz
/// </summary>
inline void config_72mhz_hclk()
{
	PllInitOptions pll_init_options;
	pll_init_options._state = PllState::On;
	pll_init_options._clock_source = PllClockSource::HSE;
	pll_init_options._mul = PllMul::Mul9;

	OscInitOptions osc_init_options;
	osc_init_options._oscillator_type = OscillatorType::HSE;
	osc_init_options._hse_state = HseState::On;
	osc_init_options._hse_prediv = HsePrediv::DIV1;
	osc_init_options._pll_init_options = pll_init_options;
	if (Osc::Config(osc_init_options) != HAL_OK)
	{
		/* 时钟初始化失败，之后的程序将可能无法正常执行，可以在这里加入自己的处理 */
		while (1);
	}

	ClockInitOptions clock_init_options;
	clock_init_options._clock_type = ClockType::SYSCLK
		| ClockType::HCLK
		| ClockType::PCLK1
		| ClockType::PCLK2;
	clock_init_options._sysclk_source = SysclkSource::PLLCLK;
	clock_init_options._ahb_clk_divider = AHBDivider::DIV1;
	clock_init_options._apb1_divider = APBDivider::DIV2;
	clock_init_options._apb2_divider = APBDivider::DIV1;
	if (Clock::Config(clock_init_options, FlashLatency::Latency2) != HAL_OK)
	{
		/* 时钟初始化失败，之后的程序将可能无法正常执行，可以在这里加入自己的处理 */
		while (1);
	}
}
