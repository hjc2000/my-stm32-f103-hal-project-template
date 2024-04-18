#include"Uart.h"

using namespace std;
using namespace hal;

hal::UartInitOptions::UartInitOptions(UART_InitTypeDef const &value)
{
	*this = value;
}

UartInitOptions &hal::UartInitOptions::operator=(UART_InitTypeDef const &value)
{
	_baud_rate = value.BaudRate;
	_word_length = (UartWordLength)value.WordLength;
	_stop_bit_count = (UartStopBitCount)value.StopBits;
	_parity = (UartParity)value.Parity;
	_mode = (UartMode)value.Mode;
	_hw_flow_ctl = (UartHardwareFlowControl)value.HwFlowCtl;
	_over_sampling = (UartOverSample)value.OverSampling;
	return *this;
}

hal::UartInitOptions::operator UART_InitTypeDef() const
{
	UART_InitTypeDef def;
	def.BaudRate = _baud_rate;
	def.WordLength = (uint32_t)_word_length;
	def.StopBits = (uint32_t)_stop_bit_count;
	def.Parity = (uint32_t)_parity;
	def.Mode = (uint32_t)_mode;
	def.HwFlowCtl = (uint32_t)_hw_flow_ctl;
	def.OverSampling = (uint32_t)_over_sampling;
	return def;
}

bool hal::Uart::IsClockEnabled()
{
	return false;
}

void hal::Uart::EnableClock()
{
}

void hal::Uart::DisableClock()
{
}

void hal::Uart::Initialize(UartInitOptions const &options)
{
	UART_HandleTypeDef def;
	def.Instance = &HardwareInstance();
	def.Init = options;
	HAL_UART_Init(&def);
}
