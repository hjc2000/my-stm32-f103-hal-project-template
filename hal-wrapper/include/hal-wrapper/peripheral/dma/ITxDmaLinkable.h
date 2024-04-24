#pragma once
#include<hal-wrapper/IHandleWrapper.h>
#include<hal-wrapper/peripheral/dma/IDmaChannel.h>
#include<hal.h>

namespace hal
{
	template<typename HandleType>
	class ITxDmaLinkable :public IHandleWrapper<HandleType>
	{
	public:
		/// <summary>
		///		继承自 IHandleWrapper。返回你所包装的句柄对象的指针。
		/// </summary>
		/// <returns></returns>
		virtual HandleType *Handle() = 0;

		/// <summary>
		///		返回你所包装的句柄对象中的 hdmatx 字段。
		/// </summary>
		/// <returns></returns>
		virtual DMA_HandleTypeDef *DmaTxHandle() = 0;

		/// <summary>
		///		设置你所包装的句柄对象中的 hdmatx 字段。
		/// </summary>
		/// <param name="value"></param>
		virtual void SetDmaTxHandle(DMA_HandleTypeDef *value) = 0;

		/// <summary>
		///		连接到 DMA
		/// </summary>
		/// <param name="dma"></param>
		void LinkToDma(IDmaChannel &dma)
		{
			// 将 dma 的父亲设为本对象所包装的句柄
			dma.Handle()->Parent = Handle();
			SetDmaTxHandle(dma.Handle());
		}
	};
}
