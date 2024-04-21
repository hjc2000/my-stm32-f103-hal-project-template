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

	};
}