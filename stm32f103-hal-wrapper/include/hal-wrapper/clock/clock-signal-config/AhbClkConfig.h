#pragma once
#include<hal.h>
#include<hal-wrapper/clock/clock-signal-config/ApbClkConfig.h>

namespace hal
{
	class AhbClkConfig
	{
	public:
		enum class InputDivider
		{
			DIV1 = RCC_SYSCLK_DIV1,
			DIV2 = RCC_SYSCLK_DIV2,
			DIV4 = RCC_SYSCLK_DIV4,
			DIV8 = RCC_SYSCLK_DIV8,
			DIV16 = RCC_SYSCLK_DIV16,
			DIV64 = RCC_SYSCLK_DIV64,
			DIV128 = RCC_SYSCLK_DIV128,
			DIV256 = RCC_SYSCLK_DIV256,
			DIV512 = RCC_SYSCLK_DIV512,
		};

		InputDivider _input_divider;
		Apb1ClkConfig _apb1_clk_config;
		Apb2ClkConfig _apb2_clk_config;

		void Serialize(RCC_ClkInitTypeDef &o) const;
		void Deserialize(RCC_ClkInitTypeDef const &o);
	};
}
