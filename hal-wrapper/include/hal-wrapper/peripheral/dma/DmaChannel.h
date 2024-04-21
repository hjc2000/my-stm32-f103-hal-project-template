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
		DMA_HandleTypeDef _handle;

	public:
		void Initialize(DmaInitOptions const &options)
		{
			_handle.Init = options;
			HAL_DMA_Init(&_handle);
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