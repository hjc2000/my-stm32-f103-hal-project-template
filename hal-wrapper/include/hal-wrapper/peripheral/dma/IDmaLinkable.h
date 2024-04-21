#pragma once
#include<hal.h>

namespace hal
{
	template<typename HandleType>
	class IDmaLinkable
	{
	public:
		virtual HandleType *Handle() = 0;

		virtual DMA_HandleTypeDef *DmaTxHandle() = 0;
		virtual void SetDmaTxHandle(DMA_HandleTypeDef *value) = 0;

		virtual DMA_HandleTypeDef *DmaRxHandle() = 0;
		virtual void SetDmaRxHandle(DMA_HandleTypeDef *value) = 0;
	};
}