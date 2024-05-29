#include"ConfigClockSignal.h"
#include<ClockSignal.h>
#include<Systic.h>

using namespace bsp;

void bsp::ConfigClockSignal()
{
	Systic::SetClockSource(SysticClockSource::HCLK_DIV8);

	ClockSignalConfig clock_init_options { };
	clock_init_options._clock_type = ClockSignalConfig::ClockType::SYSCLK
		| ClockSignalConfig::ClockType::HCLK
		| ClockSignalConfig::ClockType::PCLK1
		| ClockSignalConfig::ClockType::PCLK2;

	clock_init_options._flash_latency = ClockSignalConfig::FlashLatency::Latency2;

	clock_init_options._system_clk_config._clock_source = SystemClockConfig::ClockSource::PLLCLK;
	clock_init_options._system_clk_config._ahb_clk_config._input_divider = AhbClkConfig::InputDivider::DIV1;
	clock_init_options._system_clk_config._ahb_clk_config._apb1_clk_config._input_divider = Apb1ClkConfig::InputDivider::DIV2;
	clock_init_options._system_clk_config._ahb_clk_config._apb2_clk_config._input_divider = Apb2ClkConfig::InputDivider::DIV1;

	ClockSignal::SetConfig(clock_init_options);
}
