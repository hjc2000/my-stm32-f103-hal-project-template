#include"ApbClkConfig.h"

using namespace bsp;

void bsp::Apb1ClkConfig::Serialize(RCC_ClkInitTypeDef &o) const
{
	o.APB1CLKDivider = static_cast<uint32_t>(_input_divider);
}

void bsp::Apb1ClkConfig::Deserialize(RCC_ClkInitTypeDef const &o)
{
	_input_divider = static_cast<decltype(_input_divider)>(o.APB1CLKDivider);
}

void bsp::Apb2ClkConfig::Serialize(RCC_ClkInitTypeDef &o) const
{
	o.APB2CLKDivider = static_cast<uint32_t>(_input_divider);
}

void bsp::Apb2ClkConfig::Deserialize(RCC_ClkInitTypeDef const &o)
{
	_input_divider = static_cast<decltype(_input_divider)>(o.APB2CLKDivider);
}
