#pragma once
#include<hal-wrapper/IHandleWrapper.h>
#include<hal-wrapper/peripheral/dma/Dma.h>
#include<hal.h>

namespace hal
{
	/// <summary>
	///		本接口表明一个类可以连接到 DMA
	/// </summary>
	/// <typeparam name="HandleType"></typeparam>
	template<typename HandleType>
	class IDmaLinkable :public IHandleWrapper<HandleType>
	{
	public:
		/// <summary>
		///		继承自 IHandleWrapper
		/// </summary>
		/// <returns></returns>
		virtual HandleType *Handle() = 0;

		virtual DMA_HandleTypeDef *DmaTxHandle() = 0;
		virtual void SetDmaTxHandle(DMA_HandleTypeDef *value) = 0;

		virtual DMA_HandleTypeDef *DmaRxHandle() = 0;
		virtual void SetDmaRxHandle(DMA_HandleTypeDef *value) = 0;

		/// <summary>
		///		连接到 DMA
		/// </summary>
		/// <param name="dma"></param>
		void LinkToDma(Dma dma)
		{
			dma.Handle()->Parent = Handle();
			SetDmaTxHandle(dma.Handle());
			SetDmaRxHandle(dma.Handle());
		}
	};
}
