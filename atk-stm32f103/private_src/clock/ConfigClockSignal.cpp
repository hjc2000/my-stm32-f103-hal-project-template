#include"ConfigClockSignal.h"
#include<hal.h>
#include<hal-wrapper/clock/ClockSignal.h>
#include<hal-wrapper/clock/SysTickClock.h>

using namespace bsp;

void bsp::ConfigClockSignal()
{
	hal::SysTickClock::Instance().SetClockSource(hal::SysTickClock::SysTickClockSource::HCLK_DIV8);

	hal::ClockSignalConfig clock_init_options { };
	clock_init_options._clock_type = hal::ClockSignalConfig::ClockType::SYSCLK
		| hal::ClockSignalConfig::ClockType::HCLK
		| hal::ClockSignalConfig::ClockType::PCLK1
		| hal::ClockSignalConfig::ClockType::PCLK2;

	clock_init_options._flash_latency = hal::ClockSignalConfig::FlashLatency::Latency2;

	clock_init_options._system_clk_config._clock_source = hal::SystemClockConfig::ClockSource::PLLCLK;
	clock_init_options._system_clk_config._ahb_clk_config._input_divider = hal::AhbClkConfig::InputDivider::DIV1;
	clock_init_options._system_clk_config._ahb_clk_config._apb1_clk_config._input_divider = hal::Apb1ClkConfig::InputDivider::DIV2;
	clock_init_options._system_clk_config._ahb_clk_config._apb2_clk_config._input_divider = hal::Apb2ClkConfig::InputDivider::DIV1;

	hal::ClockSignal::SetConfig(clock_init_options);
}
