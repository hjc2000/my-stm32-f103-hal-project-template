#include"Dma1.h"

bool atk::Dma1::IsClockEnabled()
{
	return __HAL_RCC_DMA1_IS_CLK_ENABLED();
}

void atk::Dma1::EnableClock()
{
	__HAL_RCC_DMA1_CLK_ENABLE();
}

void atk::Dma1::DisableClock()
{
	__HAL_RCC_DMA1_CLK_DISABLE();
}
