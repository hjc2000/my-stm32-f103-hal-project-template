#pragma once
#include<hal.h>
#include<stdint.h>

/// <summary>
///		选择要设置的时钟信号类型。
///		本枚举类型的枚举值可以按位或，从而选中多个时钟。
/// </summary>
enum class ClockType :uint32_t
{
	SYSCLK = RCC_CLOCKTYPE_SYSCLK,
	HCLK = RCC_CLOCKTYPE_HCLK,
	PCLK1 = RCC_CLOCKTYPE_PCLK1,
	PCLK2 = RCC_CLOCKTYPE_PCLK2,
};

/// <summary>
///		选择系统时钟的时钟源
/// </summary>
enum class SysclkSource :uint32_t
{
	HSI = RCC_SYSCLKSOURCE_HSI,
	HSE = RCC_SYSCLKSOURCE_HSE,
	PLLCLK = RCC_SYSCLKSOURCE_PLLCLK,
};

/// <summary>
///		AHB 分频器的分频系数。
///		SYSCLK 经过 AHB 分频器后变成 HCLK。
/// </summary>
enum class AHBDivider :uint32_t
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

/// <summary>
///		APB1 和 APB2 分频器的分频系数。
///		HCLK 经过 APB1 分频器后变成 PCLK1，此即低速外设时钟。
///		HCLK 经过 APB2 分频器后变成 PCLK2，此即高速外设时钟。
/// </summary>
enum class APBDivider :uint32_t
{
	DIV1 = RCC_HCLK_DIV1,
	DIV2 = RCC_HCLK_DIV2,
	DIV4 = RCC_HCLK_DIV4,
	DIV8 = RCC_HCLK_DIV8,
	DIV16 = RCC_HCLK_DIV16,
};

class ClockInitOptions
{
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
};

class Clock
{
private:
	Clock() = delete;

public:
	static void InitClock(ClockInitOptions const &options)
	{

	}
};
