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
	_current_to_init = this;
	UART_HandleTypeDef def;
	def.Instance = &HardwareInstance();
	def.Init = options;
	HAL_UART_Init(&def);
	HAL_UART_Receive_IT(&def, ReceiveBuffer(), ReceiveBufferSize());
}

/// <summary>
///		为 HAL_UART_MspInit 函数提供一个全局访问点，表示当前是在初始化哪个串口。
/// </summary>
Uart *Uart::_current_to_init = nullptr;

/// <summary>
///		重写 HAL 中的 weak 版本。
///		通过全局访问点 Uart::_current_to_init 来调用具体的实例。
/// </summary>
/// <param name="huart"></param>
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	if (Uart::_current_to_init == nullptr)
	{
		return;
	}

	Uart::_current_to_init->MspInit();
}
