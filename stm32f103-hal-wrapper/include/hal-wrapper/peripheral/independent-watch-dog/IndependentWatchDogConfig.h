#pragma once
#include<bsp-interface/HandleWrapper.h>
#include<hal.h>
#include<stdint.h>

namespace hal
{
	/// <summary>
	///		看门狗初始化选项。
	/// </summary>
	class IndependentWatchDogConfig :
		public bsp::HandleWrapper<IWDG_InitTypeDef>
	{
	private:
		IWDG_InitTypeDef _config_handle;

	public:
		IndependentWatchDogConfig() = default;
		IndependentWatchDogConfig(IWDG_InitTypeDef const &o);
		IndependentWatchDogConfig &operator=(IWDG_InitTypeDef const &o);

		IWDG_InitTypeDef &Handle() override;

		/// <summary>
		///		看门狗预分频器分频系数
		/// </summary>
		enum class PrescalerOption
		{
			Div4 = IWDG_PRESCALER_4,
			Div8 = IWDG_PRESCALER_8,
			Div16 = IWDG_PRESCALER_16,
			Div32 = IWDG_PRESCALER_32,
			Div64 = IWDG_PRESCALER_64,
			Div128 = IWDG_PRESCALER_128,
			Div256 = IWDG_PRESCALER_256,
		};

		/// <summary>
		///		看门狗预分频器分频系数。
		/// </summary>
		PrescalerOption Prescaler();
		void SetPrescaler(PrescalerOption value);

		uint8_t GetPrescalerByPow();
		void SetPrescalerByPow(uint8_t pow);

		/// <summary>
		///		看门狗重载值。允许的范围：[0, 0x0FFF]
		/// </summary>
		uint32_t ReloadValue();
		void SetReloadValue(uint32_t value);
	};
}
