#pragma once
#include<hal-wrapper/clock/OscInitOptions.h>
#include<hal-wrapper/clock/PllInitOptions.h>
#include<hal.h>

namespace hal
{
	/// <summary>
	///		时钟系统只有一个，所以实现为静态类
	/// </summary>
	class Osc
	{
	private:
		Osc() = delete;

	public:
		/// <summary>
		///		配置时钟源
		/// </summary>
		/// <param name="options"></param>
		/// <returns></returns>
		static HAL_StatusTypeDef Config(OscInitOptions const &options)
		{
			RCC_OscInitTypeDef rcc_osc_init = options;
			return HAL_RCC_OscConfig(&rcc_osc_init);
		}
	};
}
