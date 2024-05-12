#pragma once
#include<PllInitOptions.h>
#include<hal.h>

namespace atk
{
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

	enum class HsePrediv
	{
		DIV1 = RCC_HSE_PREDIV_DIV1,
		DIV2 = RCC_HSE_PREDIV_DIV2,
	};

	enum class LseState
	{
		Off = RCC_LSE_OFF,
		On = RCC_LSE_ON,
		Bypass = RCC_LSE_BYPASS,
	};

	enum class HsiState
	{
		Off = RCC_HSI_OFF,
		On = RCC_HSI_ON,
	};

	enum class LsiState
	{
		Off = RCC_LSI_OFF,
		On = RCC_LSI_ON,
	};

	/// <summary>
	///		振荡器配置。（或者说时钟源配置）
	/// </summary>
	class OscInitOptions
	{
	public:
		OscInitOptions() {}

		OscInitOptions(RCC_OscInitTypeDef const &def)
		{
			*this = def;
		}

		/// <summary>
		///		提供用 hal 库中的 RCC_OscInitTypeDef 类对象来初始化本类对象的方法。
		/// </summary>
		/// <param name="value"></param>
		/// <returns></returns>
		OscInitOptions &operator=(RCC_OscInitTypeDef const &value);

		OscillatorType _oscillator_type = OscillatorType::HSI;

		HseState _hse_state = HseState::Off;
		HsePrediv _hse_prediv = HsePrediv::DIV1;
		LseState _lse_state = LseState::Off;
		HsiState _hsi_state = HsiState::On;

		/// <summary>
		///		必须在区间 [0x00, 0x1f] 上
		/// </summary>
		uint32_t _hsi_calibration_value = RCC_HSICALIBRATION_DEFAULT;

		LsiState _lsi_state = LsiState::Off;

		PllInitOptions _pll_init_options;

		operator RCC_OscInitTypeDef() const;
	};
}