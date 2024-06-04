#include"IndependentWatchDog.h"

using namespace hal;

void IndependentWatchDog::Initialize(IndependentWatchDogConfig &config)
{
	Handle()->Instance = HardwareInstance();
	Handle()->Init = config.Handle();
	HAL_IWDG_Init(Handle());
}

uint32_t IndependentWatchDog::PrescalerValue()
{
	switch (Prescaler())
	{
	case IndependentWatchDogConfig::PrescalerOption::Div4:
		{
			return 4;
		}
	case IndependentWatchDogConfig::PrescalerOption::Div8:
		{
			return 8;
		}
	case IndependentWatchDogConfig::PrescalerOption::Div16:
		{
			return 16;
		}
	case IndependentWatchDogConfig::PrescalerOption::Div32:
		{
			return 32;
		}
	case IndependentWatchDogConfig::PrescalerOption::Div64:
		{
			return 64;
		}
	case IndependentWatchDogConfig::PrescalerOption::Div128:
		{
			return 128;
		}
	case IndependentWatchDogConfig::PrescalerOption::Div256:
		{
			return 256;
		}
	default:
		{
			throw std::invalid_argument { "Prescaler() 的值非法" };
		}
	}
}

std::chrono::milliseconds IndependentWatchDog::WatchDogTimeoutDuration()
{
	return std::chrono::milliseconds {
		(uint64_t)1000 * Handle()->Init.Reload * InnerClockSourceFreq_Hz() / PrescalerValue()
	};
}

void IndependentWatchDog::SetWatchDogTimeoutDuration(std::chrono::milliseconds value)
{
	/*
	* 计数器的计数周期为：
	*	T = 1 / CounterFreq_Hz()
	* 单位是秒。
	* value 化成秒是：
	*	seconds = value / 1000
	* 想要持续 seconds 秒，计数值是：
	*	count = seconds / T
	*	count = value / 1000 / T
	*	count = value / 1000 * CounterFreq_Hz()
	* 先乘再除可以防止截断误差
	*	count = value * CounterFreq_Hz() / 1000
	*	count = value * InnerClockSourceFreq_Hz() / PrescalerValue() / 1000
	*	count * PrescalerValue() = value * InnerClockSourceFreq_Hz() / 1000
	*
	* count * PrescalerValue() 是具有物理意义的。分频器也可以看作是计数器，分频器计数满了，
	* 进位给计数器，就实现分频了。看门狗的分频系数都是 2 的整数次幂，从 4 到 256，我们只需要
	* 找出不让计数器溢出的最小分频系数。
	*/

	// 所需的 (分频器计数值 + 计数器计数值)
	uint64_t total_count = value.count() * InnerClockSourceFreq_Hz() / 1000;
	IndependentWatchDogConfig options;

	// 让计数器重装载值尽量大，溢出了就增大分频系数
	for (uint16_t i = 2; i <= 8; i++)
	{
		// 从 2^2 = 4 开始，到 2^8 = 256，通过移位实现幂。i 代表的是 2 的幂
		uint16_t prescaler_value = static_cast<uint16_t>(1 << i);
		options.SetReloadValue(total_count / prescaler_value);
		if (options.ReloadValue() > 0X0FFF && i == 8)
		{
			// 最大分频和最大计数都无法表示这个时间，就按照能达到的最大值来。
			options.SetReloadValue(0X0FFF);
			options.SetPrescaler(IndependentWatchDogConfig::PrescalerOption::Div256);
			break;
		}

		if (options.ReloadValue() <= 0x0FFF)
		{
			// i 代表的是 2 的幂，将 i 映射到分频系数枚举值
			options.SetPrescalerByPow(i);
			break;
		}
	}

	Initialize(options);
}

void IndependentWatchDog::Feed()
{
	HAL_IWDG_Refresh(Handle());
}
