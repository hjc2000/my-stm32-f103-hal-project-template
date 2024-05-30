#pragma once
#include<hal.h>

namespace hal
{
	class Apb1ClkConfig
	{
	public:
		enum class InputDivider
		{
			DIV1 = RCC_HCLK_DIV1,
			DIV2 = RCC_HCLK_DIV2,
			DIV4 = RCC_HCLK_DIV4,
			DIV8 = RCC_HCLK_DIV8,
			DIV16 = RCC_HCLK_DIV16,
		};

		InputDivider _input_divider;

		void Serialize(RCC_ClkInitTypeDef &o) const;
		void Deserialize(RCC_ClkInitTypeDef const &o);
	};

	class Apb2ClkConfig
	{
	public:
		enum class InputDivider
		{
			DIV1 = RCC_HCLK_DIV1,
			DIV2 = RCC_HCLK_DIV2,
			DIV4 = RCC_HCLK_DIV4,
			DIV8 = RCC_HCLK_DIV8,
			DIV16 = RCC_HCLK_DIV16,
		};

		InputDivider _input_divider;

		void Serialize(RCC_ClkInitTypeDef &o) const;
		void Deserialize(RCC_ClkInitTypeDef const &o);
	};
}