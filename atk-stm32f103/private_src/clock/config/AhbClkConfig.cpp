#include"AhbClkConfig.h"

using namespace bsp;

void bsp::AhbClkConfig::Serialize(RCC_ClkInitTypeDef &o) const
{
	o.AHBCLKDivider = static_cast<uint32_t>(_input_divider);
	_apb1_clk_config.Serialize(o);
	_apb2_clk_config.Serialize(o);
}

void bsp::AhbClkConfig::Deserialize(RCC_ClkInitTypeDef const &o)
{
	_input_divider = static_cast<decltype(_input_divider)>(o.AHBCLKDivider);
	_apb1_clk_config.Deserialize(o);
	_apb2_clk_config.Deserialize(o);
}
