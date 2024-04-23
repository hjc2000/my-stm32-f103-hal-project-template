#pragma once
#include<chrono>
#include<hal-wrapper/IHandleWrapper.h>
#include<hal-wrapper/IHardwareInstanceWrapper.h>
#include<hal-wrapper/peripheral/watch-dog/WatchDogInitOptions.h>

namespace hal
{
	/// <summary>
	///		独立看门狗。
	///		- 所谓独立看门狗就是具有自己的内部时钟源，不依赖单片机的系统时钟。
	///		  在系统时钟失效时仍然能工作。
	/// </summary>
	class IndependentWatchDog :
		public IHandleWrapper<IWDG_HandleTypeDef>,
		public IHardwareInstanceWrapper<IWDG_TypeDef>
	{
		IWDG_HandleTypeDef _handle;

	public:
		static IndependentWatchDog &Instance()
		{
			static IndependentWatchDog o;
			return o;
		}

		IWDG_HandleTypeDef *Handle() override
		{
			return &_handle;
		}

		IWDG_TypeDef *HardwareInstance() override
		{
			return IWDG;
		}

		void Initialize(WatchDogInitOptions const &options);

		/// <summary>
		///		通过定时的毫秒数来初始化看门狗。
		///		- 如果设置的毫秒数超出了能力范围，则会使用能达到的最大计时时间。
		/// </summary>
		/// <param name="period"></param>
		void Initialize(std::chrono::milliseconds period);

		/// <summary>
		///		分频系数。
		/// </summary>
		/// <returns></returns>
		WatchDogPrescaler Prescaler()
		{
			return WatchDogPrescaler(Handle()->Init.Prescaler);
		}

		uint32_t PrescalerValue();

		uint32_t InnerClockSourceFreq_Hz()
		{
			// 独立看门狗具有 40 kHz 的内部时钟。
			return 40 * 1000;
		}

		/// <summary>
		///		看门狗超时时间。
		/// </summary>
		/// <returns></returns>
		std::chrono::milliseconds Period_milliseconds()
		{
			return std::chrono::milliseconds{ (uint64_t)1000 * Handle()->Init.Reload * InnerClockSourceFreq_Hz() / PrescalerValue() };
		}

		/// <summary>
		///		喂狗
		/// </summary>
		void Feed()
		{
			HAL_IWDG_Refresh(Handle());
		}
	};
}