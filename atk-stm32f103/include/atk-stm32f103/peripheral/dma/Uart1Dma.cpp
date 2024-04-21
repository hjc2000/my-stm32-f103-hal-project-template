#include"Uart1Dma.h"

bool atk::Uart1Dma::IsClockEnabled()
{
	return __HAL_RCC_DMA1_IS_CLK_ENABLED();
}

void atk::Uart1Dma::EnableClock()
{
	__HAL_RCC_DMA1_CLK_ENABLE();
}

void atk::Uart1Dma::DisableClock()
{
	__HAL_RCC_DMA1_CLK_DISABLE();
}
