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
	class IIndependentWatchDog :
		public IHandleWrapper<IWDG_HandleTypeDef>,
		public IHardwareInstanceWrapper<IWDG_TypeDef>
	{
	public:
		void Initialize(WatchDogInitOptions const &options)
		{
			Handle()->Instance = HardwareInstance();
			Handle()->Init = options;
			HAL_IWDG_Init(Handle());
		}

		/// <summary>
		///		分频系数。
		/// </summary>
		/// <returns></returns>
		WatchDogPrescaler Prescaler()
		{
			return WatchDogPrescaler(Handle()->Init.Prescaler);
		}

		uint32_t PrescalerValue();

		/// <summary>
		///		独立看门狗内部时钟源的频率。单位：Hz。
		/// </summary>
		/// <returns></returns>
		virtual uint32_t InnerClockSourceFreq_Hz() = 0;

		/// <summary>
		///		InnerClockSourceFreq_Hz 经过分频后，输入到计数器中的频率。
		/// </summary>
		/// <returns></returns>
		uint32_t CounterFreq_Hz()
		{
			return InnerClockSourceFreq_Hz() / PrescalerValue();
		}

		/// <summary>
		///		看门狗超时时间。
		/// </summary>
		/// <returns></returns>
		std::chrono::milliseconds Period_milliseconds()
		{
			return std::chrono::milliseconds{ 1000 * Handle()->Init.Reload * CounterFreq_Hz() };
		}

		void FeedDog()
		{
			HAL_IWDG_Refresh(Handle());
		}
	};
}