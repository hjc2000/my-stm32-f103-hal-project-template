#pragma once
#include<hal-wrapper/peripheral/dma/DmaInitOptions.h>

namespace hal
{
	/// <summary>
	///		DMA 通道抽象类
	/// </summary>
	class IDmaChannel
	{
	public:
		virtual DMA_Channel_TypeDef *HardwareInstance() = 0;

		/// <summary>
		///		本对象内部的 DMA_HandleTypeDef 句柄对象的指针。
		/// </summary>
		/// <returns></returns>
		virtual DMA_HandleTypeDef *Handle() = 0;

		/// <summary>
		///		DMA 传输完成。
		/// </summary>
		/// <returns>传输完成返回 true，否则返回 false。</returns>
		bool TransferCompleted()
		{
			return __HAL_DMA_GET_FLAG(Handle(), DMA_FLAG_TC4);
		}

		/// <summary>
		///		清除 DMA 传输完成标志。
		/// </summary>
		void ClearTransferCompletedFlag()
		{
			__HAL_DMA_CLEAR_FLAG(Handle(), DMA_FLAG_TC4);
		}
	};
}
