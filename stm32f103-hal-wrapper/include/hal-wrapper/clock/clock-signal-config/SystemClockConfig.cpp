#include"SystemClockConfig.h"

using namespace hal;

void hal::SystemClockConfig::Serialize(RCC_ClkInitTypeDef &o) const
{
	o.SYSCLKSource = static_cast<uint32_t>(_clock_source);
	_ahb_clk_config.Serialize(o);
}

void hal::SystemClockConfig::Deserialize(RCC_ClkInitTypeDef const &o)
{
	_clock_source = static_cast<decltype(_clock_source)>(o.SYSCLKSource);
	_ahb_clk_config.Deserialize(o);
}
