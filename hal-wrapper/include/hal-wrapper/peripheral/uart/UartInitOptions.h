#pragma once
#include<hal-wrapper/peripheral/uart/UartEnum.h>

namespace hal
{
	/// <summary>
	///		串口初始化选项
	/// </summary>
	class UartInitOptions
	{
	public:
		UartInitOptions() = default;
		UartInitOptions(UartInitOptions const &value) = default;
		UartInitOptions(UART_InitTypeDef const &value);
		UartInitOptions &operator=(UartInitOptions const &value) = default;
		UartInitOptions &operator=(UART_InitTypeDef const &value);

		/// <summary>
		///		波特率
		/// </summary>
		uint32_t _baud_rate = 115200;

		/// <summary>
		///		一个串行帧有多少位
		/// </summary>
		UartWordLength _word_length = UartWordLength::WordLength_8bit;

		/// <summary>
		///		一个串行帧有多少个停止位
		/// </summary>
		UartStopBitCount _stop_bit_count = UartStopBitCount::StopBitCount_1bit;

		/// <summary>
		///		校验模式。
		///		- 校验位被放到串行帧中除了停止位以外的最高位。
		/// </summary>
		UartParity _parity = UartParity::None;

		/// <summary>
		///		收发模式
		/// </summary>
		UartMode _mode = UartMode::RX_TX;

		/// <summary>
		///		硬件流控
		/// </summary>
		UartHardwareFlowControl _hw_flow_ctl = UartHardwareFlowControl::None;

		/// <summary>
		///		过采样倍率
		/// </summary>
		UartOverSample _over_sampling = UartOverSample::OverSample_16;

		operator UART_InitTypeDef() const;
	};
}
