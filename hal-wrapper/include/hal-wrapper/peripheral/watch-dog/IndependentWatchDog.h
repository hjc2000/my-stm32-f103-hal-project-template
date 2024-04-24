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
	private:
		IWDG_HandleTypeDef _handle;
		void Initialize(WatchDogInitOptions const &options);

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
		///		内部时钟信号的频率。还要经过预分频才会输入到计数器。
		/// </summary>
		/// <returns></returns>
		constexpr uint32_t InnerClockSourceFreq_Hz()
		{
			// 独立看门狗具有 40 kHz 的内部时钟。
			return 40 * 1000;
		}

		#pragma region IWatchDog
		std::chrono::milliseconds WatchDogTimeoutDuration() override;
		void SetWatchDogTimeoutDuration(std::chrono::milliseconds value) override;
		void Feed() override;
		#pragma endregion

	};
}