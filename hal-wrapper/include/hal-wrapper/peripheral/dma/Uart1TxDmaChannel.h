#pragma once
#include<hal-wrapper/IClockSwitchable.h>
#include<hal-wrapper/peripheral/dma/IDmaChannel.h>

namespace hal
{
	/// <summary>
	///		UART1 的发送 DMA 通道。
	/// </summary>
	class Uart1TxDmaChannel :
		public hal::IDmaChannel,
		public hal::IClockSwitchable
	{
	private:
		DMA_HandleTypeDef _handle;

		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;

	public:
		Uart1TxDmaChannel();

		DMA_Channel_TypeDef *HardwareInstance() override;

		static Uart1TxDmaChannel &Instance()
		{
			static Uart1TxDmaChannel o;
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