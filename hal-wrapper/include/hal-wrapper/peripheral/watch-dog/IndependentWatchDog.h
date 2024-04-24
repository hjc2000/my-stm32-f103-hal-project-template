#pragma once
#include<bsp-interface/IWatchDog.h>
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
		public IHardwareInstanceWrapper<IWDG_TypeDef>,
		public bsp::IWatchDog
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

		#pragma region IWatchDog
		std::chrono::milliseconds WatchDogTimeoutDuration() override
		{
			return std::chrono::milliseconds{ (uint64_t)1000 * Handle()->Init.Reload * InnerClockSourceFreq_Hz() / PrescalerValue() };
		}

		void SetWatchDogTimeoutDuration(std::chrono::milliseconds value) override;

		void Feed() override
		{
			HAL_IWDG_Refresh(Handle());
		}
		#pragma endregion

	};
}