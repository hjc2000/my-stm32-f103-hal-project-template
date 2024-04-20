#include"Uart1.h"

using namespace atk;
using namespace hal;

void atk::Uart1::MspInit(UART_HandleTypeDef *huart)
{
	GpioPortA::Instance().EnableClock();
	Uart1::Instance().EnableClock();

	// 发送引脚 PA9，接收引脚 PA10。
	GpioPinInitOptions options;
	options._mode = GpioPinMode::Output_PushPull;
	options._pull_mode = GpioPinPull::PullUp;
	options._speed = GpioPinSpeed::High;
	GpioPortA::Instance().InitPin(GpioPin::Pin9, options);
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
