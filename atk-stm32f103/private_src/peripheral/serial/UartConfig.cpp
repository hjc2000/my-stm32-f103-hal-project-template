#include"UartConfig.h"

using namespace bsp;

bsp::UartConfig::UartConfig(UART_InitTypeDef const &o)
{
	*this = o;
}

UartConfig &bsp::UartConfig::operator=(UART_InitTypeDef const &o)
{
	_baud_rate = o.BaudRate;
	_word_length = (UartWordLength)o.WordLength;
	_stop_bit_count = (UartStopBitCount)o.StopBits;
	_parity = (UartParity)o.Parity;
	_mode = (UartMode)o.Mode;
	_hw_flow_ctl = (UartHardwareFlowControl)o.HwFlowCtl;
	_over_sampling = (UartOverSample)o.OverSampling;
	return *this;
}

bsp::UartConfig::operator UART_InitTypeDef() const
{
	UART_InitTypeDef o;
	o.BaudRate = _baud_rate;
	o.WordLength = (uint32_t)_word_length;
	o.StopBits = (uint32_t)_stop_bit_count;
	o.Parity = (uint32_t)_parity;
	o.Mode = (uint32_t)_mode;
	o.HwFlowCtl = (uint32_t)_hw_flow_ctl;
	o.OverSampling = (uint32_t)_over_sampling;
	return o;
}
