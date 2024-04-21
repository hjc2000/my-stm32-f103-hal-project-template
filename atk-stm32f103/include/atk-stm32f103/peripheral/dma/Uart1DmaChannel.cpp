#include"Uart1DmaChannel.h"

bool atk::Uart1DmaChannel::IsClockEnabled()
{
	return __HAL_RCC_DMA1_IS_CLK_ENABLED();
}

void atk::Uart1DmaChannel::EnableClock()
{
	__HAL_RCC_DMA1_CLK_ENABLE();
}

void atk::Uart1DmaChannel::DisableClock()
{
	__HAL_RCC_DMA1_CLK_DISABLE();
}
