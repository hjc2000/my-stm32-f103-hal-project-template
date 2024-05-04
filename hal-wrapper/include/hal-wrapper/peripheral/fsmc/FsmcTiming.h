#pragma once
#include<hal.h>

namespace hal
{
	class FsmcNorSramTiming
	{
	public:
		FsmcNorSramTiming() = default;
		FsmcNorSramTiming(FSMC_NORSRAM_TimingTypeDef const &o);
		FsmcNorSramTiming &operator=(FSMC_NORSRAM_TimingTypeDef const &o);

		/// <summary>
		///		地址建立时间。
		///		* 单位：HCLK 的周期数
		///		* 取值范围：[0, 15]
		///		* 同步模式下本参数不被使用。
		/// </summary>
		uint32_t _address_setup_time;

		/// <summary>
		///		地址保持时间。
		///		* 单位：HCLK 的周期数
		///		* 取值范围：[0, 15]
		///		* 同步模式下本参数不被使用。
		/// </summary>
		uint32_t _address_hold_time;

		/// <summary>
		///		数据建立时间。
		///		* 单位：HCLK 的周期数
		///		* 取值范围：[1, 255]
		/// </summary>
		uint32_t _data_setup_time;

		/// <summary>
		///		* 单位：HCLK 的周期数
		///		* 取值范围：[0, 15]
		/// </summary>
		uint32_t _bus_turn_around_duration;

		/// <summary>
		///		* 单位：HCLK 的周期数
		///		* 取值范围：[2, 16]
		/// </summary>
		uint32_t _clk_division;

		uint32_t _data_latency;

		enum class AccessMode
		{
			ModeA = FSMC_ACCESS_MODE_A,
			ModeB = FSMC_ACCESS_MODE_B,
			ModeC = FSMC_ACCESS_MODE_C,
			ModeD = FSMC_ACCESS_MODE_D,
		};

		AccessMode _access_mode;

		operator FSMC_NORSRAM_TimingTypeDef() const;
	};
}
