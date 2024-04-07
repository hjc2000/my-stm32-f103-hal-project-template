#pragma once
// 这个头文件要最先包含，所以放到双引号里，避免 vs 的头文件排序把它放到后面去
#include"stm32f1xx_hal.h"
#include<stdint.h>
#include<stm32f1xx_hal_def.h>
#include<stm32f1xx_hal_rcc.h>

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
	#ifdef RCC_PLL_MUL2
	Mul2 = RCC_PLL_MUL2,
	#endif // RCC_PLL_MUL2

	#ifdef RCC_PLL_MUL3
	Mul3 = RCC_PLL_MUL3,
	#endif // RCC_PLL_MUL3

	#ifdef RCC_PLL_MUL4
	Mul4 = RCC_PLL_MUL4,
	#endif // RCC_PLL_MUL4

	#ifdef RCC_PLL_MUL5
	Mul5 = RCC_PLL_MUL5,
	#endif // RCC_PLL_MUL5

	#ifdef RCC_PLL_MUL6
	Mul6 = RCC_PLL_MUL6,
	#endif // RCC_PLL_MUL6

	#ifdef RCC_PLL_MUL7
	Mul7 = RCC_PLL_MUL7,
	#endif // RCC_PLL_MUL7

	#ifdef RCC_PLL_MUL8
	Mul8 = RCC_PLL_MUL8,
	#endif // RCC_PLL_MUL8

	#ifdef RCC_PLL_MUL9
	Mul9 = RCC_PLL_MUL9,
	#endif // RCC_PLL_MUL9

	#ifdef RCC_PLL_MUL10
	Mul10 = RCC_PLL_MUL10,
	#endif // RCC_PLL_MUL10

	#ifdef RCC_PLL_MUL11
	Mul11 = RCC_PLL_MUL11,
	#endif // RCC_PLL_MUL11

	#ifdef RCC_PLL_MUL12
	Mul12 = RCC_PLL_MUL12,
	#endif // RCC_PLL_MUL12

	#ifdef RCC_PLL_MUL13
	Mul13 = RCC_PLL_MUL13,
	#endif // RCC_PLL_MUL13

	#ifdef RCC_PLL_MUL14
	Mul14 = RCC_PLL_MUL14,
	#endif // RCC_PLL_MUL14

	#ifdef RCC_PLL_MUL15
	Mul15 = RCC_PLL_MUL15,
	#endif // RCC_PLL_MUL15

	#ifdef RCC_PLL_MUL16
	Mul16 = RCC_PLL_MUL16,
	#endif // RCC_PLL_MUL16
};

/// <summary>
///		PLL 初始化选项
/// </summary>
class PllInitOptions
{
public:
	PllInitOptions() {}

	PllInitOptions(RCC_PLLInitTypeDef def)
	{
		_state = (PllState)def.PLLState;
		_clock_source = (PllClockSource)def.PLLSource;
		_mul = (PllMul)def.PLLMUL;
	}

public:
	PllState _state = PllState::On;

	PllClockSource _clock_source = PllClockSource::HSE;

	/// <summary>
	///		倍频系数
	/// </summary>
	PllMul _mul = PllMul::Mul9;

public:
	operator RCC_PLLInitTypeDef()
	{
		RCC_PLLInitTypeDef def;
		def.PLLState = (uint32_t)_state;
		def.PLLSource = (uint32_t)_clock_source;
		def.PLLMUL = (uint32_t)_mul;
		return def;
	}
};






enum class OscillatorType
{
	NONE = RCC_OSCILLATORTYPE_NONE,
	HSE = RCC_OSCILLATORTYPE_HSE,
	HSI = RCC_OSCILLATORTYPE_HSI,
	LSE = RCC_OSCILLATORTYPE_LSE,
	LSI = RCC_OSCILLATORTYPE_LSI,
};

enum class HseState
{
	Off = RCC_HSE_OFF,
	On = RCC_HSE_ON,
	Bypass = RCC_HSE_BYPASS,
};

class OscInitOptions
{
public:
	OscillatorType _oscillator_type = OscillatorType::HSI;
	HseState _hse_state = HseState::Off;

	/// <summary>
	///		HSE 预分频系数。
	///		可选值：
	///			RCC_HSE_PREDIV_DIV1
	///			RCC_HSE_PREDIV_DIV2
	/// </summary>
	uint32_t HSEPredivValue;       /*!<  The Prediv1 factor value (named PREDIV1 or PLLXTPRE in RM)
	This parameter can be a value of @ref RCCEx_Prediv1_Factor */

	uint32_t LSEState;              /*!<  The new state of the LSE.
	This parameter can be a value of @ref RCC_LSE_Config */

	uint32_t HSIState;              /*!< The new state of the HSI.
	This parameter can be a value of @ref RCC_HSI_Config */

	uint32_t HSICalibrationValue;   /*!< The HSI calibration trimming value (default is RCC_HSICALIBRATION_DEFAULT).
	This parameter must be a number between Min_Data = 0x00 and Max_Data = 0x1F */

	uint32_t LSIState;              /*!<  The new state of the LSI.
	This parameter can be a value of @ref RCC_LSI_Config */


	PllInitOptions _pll_init_options;
};
