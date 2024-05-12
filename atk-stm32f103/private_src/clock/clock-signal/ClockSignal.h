#pragma once
#include<ClockSignalInitOptions.h>
#include<hal.h>
#include<stdint.h>

namespace bsp
{
	class ClockSignal
	{
	private:
		ClockSignal() = delete;
		ClockSignal(ClockSignal const &o) = delete;
		ClockSignal(ClockSignal const &&o) = delete;
		ClockSignal &operator=(ClockSignal const &o) = delete;

	public:
		/// <summary>
		///		获取当前时钟信号的配置。
		/// </summary>
		/// <returns></returns>
		static ClockSignalConfig Config()
		{
			RCC_ClkInitTypeDef def;
			uint32_t flash_latency;
			HAL_RCC_GetClockConfig(&def, &flash_latency);
			ClockSignalConfig ret{ def };
			ret._flash_latency = static_cast<ClockSignalConfig::FlashLatency>(flash_latency);
			return ret;
		}

		/// <summary>
		///		应用时钟信号配置。
		/// </summary>
		/// <param name="config"></param>
		/// <param name="flash_latency"></param>
		/// <returns></returns>
		static void SetConfig(ClockSignalConfig const &config)
		{
			RCC_ClkInitTypeDef rcc_clk_init = config;
			HAL_StatusTypeDef ret = HAL_RCC_ClockConfig(
				&rcc_clk_init,
				static_cast<uint32_t>(config._flash_latency)
			);

			if (ret != HAL_StatusTypeDef::HAL_OK)
			{
				throw std::runtime_error{ "时钟信号配置失败" };
			}
		}
	};
}
