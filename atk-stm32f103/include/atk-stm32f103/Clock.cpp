#include"atk-stm32f103/Clock.h"

using namespace hal;
using namespace atk;

void atk::config_72mhz_hclk()
{
	OscInitOptions osc_init_options;
	osc_init_options._oscillator_type = OscillatorType::HSE;
	osc_init_options._hse_state = HseState::On;
	osc_init_options._hse_prediv = HsePrediv::DIV1;
	osc_init_options._pll_init_options._state = PllState::On;
	osc_init_options._pll_init_options._clock_source = PllClockSource::HSE;
	osc_init_options._pll_init_options._mul = PllMul::Mul9;
	if (Osc::Config(osc_init_options) != HAL_OK)
	{
		/* 时钟初始化失败，之后的程序将可能无法正常执行，可以在这里加入自己的处理 */
		while (1);
	}

	ClockSignalInitOptions clock_init_options;
	clock_init_options._clock_type = ClockType::SYSCLK
		| ClockType::HCLK
		| ClockType::PCLK1
		| ClockType::PCLK2;
	clock_init_options._sysclk_source = SysclkSource::PLLCLK;
	clock_init_options._ahb_clk_divider = AHBDivider::DIV1;
	clock_init_options._apb1_divider = APBDivider::DIV2;
	clock_init_options._apb2_divider = APBDivider::DIV1;
	if (ClockSignal::Config(clock_init_options, FlashLatency::Latency2) != HAL_OK)
	{
		/* 时钟初始化失败，之后的程序将可能无法正常执行，可以在这里加入自己的处理 */
		while (1);
	}
}
