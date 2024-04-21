#pragma once
#include<hal-wrapper/IHandleWrapper.h>
#include<hal-wrapper/peripheral/IPeripheral.h>
#include<hal-wrapper/peripheral/dma/DmaInitOptions.h>

namespace hal
{
	/// <summary>
	///		DMA 通道抽象类
	/// </summary>
	class DmaChannel :
		public IPeripheral<DMA_Channel_TypeDef>,
		public IHandleWrapper<DMA_HandleTypeDef>
	{
	public:
		/// <summary>
		///		DMA 传输完成
		/// </summary>
		/// <returns></returns>
		bool TransferCompleted()
		{
			return __HAL_DMA_GET_FLAG(Handle(), DMA_FLAG_TC4);
		}

		void ClearTransferCompletedFlag()
		{
			__HAL_DMA_CLEAR_FLAG(Handle(), DMA_FLAG_TC4);
		}
	};
}