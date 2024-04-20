#include"Uart1.h"

using namespace atk;
using namespace hal;

#ifdef USART1
void atk::Uart1::MspInit(UART_HandleTypeDef *huart)
{
	GpioPortA::Instance().EnableClock();

}

bool atk::Uart1::IsClockEnabled()
{
	return __HAL_RCC_USART1_IS_CLK_ENABLED();
}

void atk::Uart1::EnableClock()
{
	__HAL_RCC_USART1_CLK_ENABLE();
}

void atk::Uart1::DisableClock()
{
	__HAL_RCC_USART1_CLK_DISABLE();
}

hal::UartCallbackFunc atk::Uart1::MspInitCallback()
{
	return MspInit;
}

hal::UartCallbackFunc atk::Uart1::ReceiveCompleteCallback()
{
	return nullptr;
}

USART_TypeDef *atk::Uart1::HardwareInstance()
{
	return USART1;
}

uint8_t *atk::Uart1::ReceiveBuffer()
{
	return _receive_buffer;
}

uint16_t atk::Uart1::ReceiveBufferSize()
{
	return _receive_buffer_size;
}
#endif // USART1
