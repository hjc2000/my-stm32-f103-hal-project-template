#pragma once
#include<hal.h>

namespace bsp
{
	/// <summary>
	///		PLL 状态
	/// </summary>
	enum class PllState :uint32_t
	{
		NotConfigured = RCC_PLL_NONE,
		Off = RCC_PLL_OFF,
		On = RCC_PLL_ON,
	};

	/// <summary>
	///		PLL 时钟源
	/// </summary>
	enum class PllClockSource :uint32_t
	{
		HSI_DIV2 = RCC_PLLSOURCE_HSI_DIV2,
		HSE = RCC_PLLSOURCE_HSE,
	};

	/// <summary>
	///		PLL 倍频系数
	/// </summary>
	enum class PllMul :uint32_t
	{
		Mul2 = RCC_PLL_MUL2,
		Mul3 = RCC_PLL_MUL3,
		Mul4 = RCC_PLL_MUL4,
		Mul5 = RCC_PLL_MUL5,
		Mul6 = RCC_PLL_MUL6,
		Mul7 = RCC_PLL_MUL7,
		Mul8 = RCC_PLL_MUL8,
		Mul9 = RCC_PLL_MUL9,
		Mul10 = RCC_PLL_MUL10,
		Mul11 = RCC_PLL_MUL11,
		Mul12 = RCC_PLL_MUL12,
		Mul13 = RCC_PLL_MUL13,
		Mul14 = RCC_PLL_MUL14,
		Mul15 = RCC_PLL_MUL15,
		Mul16 = RCC_PLL_MUL16,
	};

	/// <summary>
	///		PLL 初始化选项
	/// </summary>
	class PllConfig
	{
	public:
		PllConfig() { }

		PllConfig(RCC_PLLInitTypeDef const &def)
		{
			*this = def;
		}

		PllConfig &operator=(RCC_PLLInitTypeDef const &value);

		PllState _state = PllState::On;

		PllClockSource _clock_source = PllClockSource::HSE;

		/// <summary>
		///		倍频系数
		/// </summary>
		PllMul _mul = PllMul::Mul9;

		operator RCC_PLLInitTypeDef() const;
	};
}
