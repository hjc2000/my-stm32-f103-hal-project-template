#pragma once
#include<hal-wrapper/IHandleWrapper.h>
#include<hal-wrapper/peripheral/IPeripheral.h>
#include<hal-wrapper/peripheral/dma/DmaInitOptions.h>
#include<hal-wrapper/peripheral/dma/IDmaLinkable.h>

namespace hal
{
	/// <summary>
	///		DMA 抽象类
	/// </summary>
	class Dma :
		public IPeripheral,
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

		template<typename HandleType>
		void SetParent(IDmaLinkable<HandleType> parant)
		{
			_handle.Parent = parant.Handle();
			parant.SetDmaRxHandle(&_handle);
			parant.SetDmaTxHandle(&_handle);
		}
	};
}