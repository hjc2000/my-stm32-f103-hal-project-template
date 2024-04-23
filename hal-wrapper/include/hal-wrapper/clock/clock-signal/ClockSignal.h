#pragma once
#include<hal-wrapper/clock/clock-signal/ClockSignalEnum.h>
#include<hal-wrapper/clock/clock-signal/ClockSignalInitOptions.h>
#include<hal.h>
#include<stdint.h>

namespace hal
{
	class ClockSignal
	{
	private:
		ClockSignal() = delete;
		ClockSignal &operator=(ClockSignal const &o) = delete;

	public:
		/// <summary>
		///		初始化时钟信号
		/// </summary>
		/// <param name="options"></param>
		/// <param name="flash_latency"></param>
		/// <returns></returns>
		static HAL_StatusTypeDef Config(ClockSignalInitOptions const &options, FlashLatency flash_latency)
		{
			RCC_ClkInitTypeDef rcc_clk_init = options;
			return HAL_RCC_ClockConfig(&rcc_clk_init, (uint32_t)flash_latency);
		}
	};
}
