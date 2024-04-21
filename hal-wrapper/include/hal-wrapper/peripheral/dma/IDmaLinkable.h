#pragma once
#include<hal-wrapper/IHandleWrapper.h>
#include<hal-wrapper/peripheral/dma/IDmaChannel.h>
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
		///		继承自 IHandleWrapper。返回你所包装的句柄对象的指针。
		/// </summary>
		/// <returns></returns>
		virtual HandleType *Handle() = 0;

		/// <summary>
		///		返回你所包装的句柄对象中的 hdmatx 字段。
		/// </summary>
		/// <returns></returns>
		virtual DMA_HandleTypeDef *DmaTxHandle() const = 0;

		/// <summary>
		///		设置你所包装的句柄对象中的 hdmatx 字段。
		/// </summary>
		/// <param name="value"></param>
		virtual void SetDmaTxHandle(DMA_HandleTypeDef *value) = 0;

		/// <summary>
		///		返回你所包装的句柄对象中的 hdmarx 字段。
		/// </summary>
		/// <returns></returns>
		virtual DMA_HandleTypeDef *DmaRxHandle() const = 0;

		/// <summary>
		///		设置你所包装的句柄对象中的 hdmarx 字段。
		/// </summary>
		/// <param name="value"></param>
		virtual void SetDmaRxHandle(DMA_HandleTypeDef *value) = 0;

		/// <summary>
		///		连接到 DMA
		/// </summary>
		/// <param name="dma"></param>
		void LinkToDma(IDmaChannel &dma)
		{
			// 将 dma 的父亲设为本对象所包装的句柄
			dma.Handle()->Parent = Handle();

			// 设置本对象所包装的句柄的 hdmarx 和 hdmatx 字段
			SetDmaTxHandle(dma.Handle());
			SetDmaRxHandle(dma.Handle());
		}
	};
}
