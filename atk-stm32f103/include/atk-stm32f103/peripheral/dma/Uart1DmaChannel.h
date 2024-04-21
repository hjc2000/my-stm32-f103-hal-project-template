#pragma once
#include<hal-wrapper/peripheral/dma/DmaChannel.h>

namespace atk
{
	class Uart1DmaChannel :public hal::DmaChannel
	{
	private:
		DMA_HandleTypeDef _handle;

		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;

	public:
		Uart1DmaChannel();

		DMA_Channel_TypeDef *HardwareInstance() override;

		static Uart1DmaChannel &Instance()
		{
			static Uart1DmaChannel o;
			return o;
		}

		/// <summary>
		///		本对象内部的 DMA_HandleTypeDef 句柄对象的指针。
		/// </summary>
		/// <returns></returns>
		DMA_HandleTypeDef *Handle() override
		{
			return &_handle;
		}
	};
}