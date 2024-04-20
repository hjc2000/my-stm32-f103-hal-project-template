#include"Uart.h"

using namespace std;
using namespace hal;

#pragma region UartInitOptions
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
#pragma endregion

void hal::Uart::Initialize(UartInitOptions const &options)
{
	_uart_handle.Instance = HardwareInstance();
	_uart_handle.Init = options;
	_uart_handle.MspInitCallback = MspInitCallback();
	HAL_UART_Init(&_uart_handle);

	/* 除了 MspInitCallback  以外的回调函数指针都会被 HAL_UART_Init 函数
	* 重置为默认的 weak 版本，所以必须在 HAL_UART_Init 函数执行后再设置这些
	* 回调函数指针。
	*/
	_uart_handle.RxCpltCallback = ReceiveCompleteCallback();
	EnableReceiveInterrupt();
}

void hal::Uart::Initialize()
{
	UartInitOptions options;
	Initialize(options);
}
