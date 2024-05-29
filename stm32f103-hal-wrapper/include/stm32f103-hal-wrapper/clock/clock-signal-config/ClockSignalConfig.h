#pragma once
#include<hal.h>
#include<stm32f103-hal-wrapper/clock/clock-signal-config/SystemClockConfig.h>

namespace hal
{
	class ClockSignalConfig
	{
	public:
		ClockSignalConfig() = default;
		ClockSignalConfig(RCC_ClkInitTypeDef const &o);
		ClockSignalConfig &operator=(RCC_ClkInitTypeDef const &o);
		operator RCC_ClkInitTypeDef() const;

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

		ClockType _clock_type;

		SystemClockConfig _system_clk_config;

		/// <summary>
		///		读写 flash 时要延迟多少个 CPU 时钟周期。
		///		CPU 时钟是由 HCLK 再经过一个分频器提供的。在 stm32f103 中，
		///		这个分频器可以选择 1 分频或 8 分频。
		/// 
		///		因为 flash 是低速储存器，CPU 时钟频率很高时会出现速度不匹配，
		///		这时候需要 CPU 通过延时来等待 flash。
		/// </summary>
		enum class FlashLatency
		{
			/// <summary>
			///		延迟 0 个 CPU 时钟周期。
			/// </summary>
			Latency0 = FLASH_LATENCY_0,

			/// <summary>
			///		延迟 1 个 CPU 时钟周期。
			/// </summary>
			Latency1 = FLASH_LATENCY_1,

			/// <summary>
			///		延迟 2 个 CPU 时钟周期。
			/// </summary>
			Latency2 = FLASH_LATENCY_2,
		};

		FlashLatency _flash_latency;

		void Serialize(RCC_ClkInitTypeDef &o) const;
		void Deserialize(RCC_ClkInitTypeDef const &o);
	};
}

/// <summary>
///		让 ClockType 枚举类型支持按位或。
/// </summary>
/// <param name="left"></param>
/// <param name="right"></param>
/// <returns></returns>
hal::ClockSignalConfig::ClockType operator|(
	hal::ClockSignalConfig::ClockType left,
	hal::ClockSignalConfig::ClockType right
	);
