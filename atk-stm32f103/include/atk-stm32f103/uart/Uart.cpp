#include"Uart.h"

using namespace atk;

bool atk::Uart1::IsClockEnabled()
{
	return false;
}

void atk::Uart1::EnableClock()
{
}

void atk::Uart1::DisableClock()
{
}

hal::UartCallbackFunc atk::Uart1::MspInitCallback()
{
	return nullptr;
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
