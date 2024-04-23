#pragma once
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
		/// <summary>
		///		独立看门狗内部时钟源的频率。单位：kHz。
		/// </summary>
		/// <returns></returns>
		virtual uint32_t InnerClockSourceFreq_kHz() = 0;

		void FeedDog()
		{
			HAL_IWDG_Refresh(Handle());
		}
	};
}