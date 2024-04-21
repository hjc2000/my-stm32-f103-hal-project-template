#pragma once
#include<hal.h>

namespace hal
{
	/// <summary>
	///		一个串行帧有多少位
	/// </summary>
	enum class UartWordLength
	{
		/// <summary>
		///		一个串行帧有 8 位。
		/// </summary>
		WordLength_8bit = UART_WORDLENGTH_8B,

		/// <summary>
		///		一个串行帧有 9 位。
		/// </summary>
		WordLength_9bit = UART_WORDLENGTH_9B,
	};

	/// <summary>
	///		有多少位停止位
	/// </summary>
	enum class UartStopBitCount
	{
		StopBitCount_1bit = UART_STOPBITS_1,
		StopBitCount_2bit = UART_STOPBITS_2,
	};

	/// <summary>
	///		UART 校验模式
	/// </summary>
	enum class UartParity
	{
		None = UART_PARITY_NONE,
		Even = UART_PARITY_EVEN,
		Odd = UART_PARITY_ODD,
	};

	/// <summary>
	///		串口收发模式。
	/// </summary>
	enum class UartMode
	{
		/// <summary>
		///		只接收
		/// </summary>
		RX = UART_MODE_RX,

		/// <summary>
		///		只发送
		/// </summary>
		TX = UART_MODE_TX,

		/// <summary>
		///		接收和发送都启用
		/// </summary>
		RX_TX = UART_MODE_TX_RX,
	};

	/// <summary>
	///		硬件流控
	/// </summary>
	enum class UartHardwareFlowControl
	{
		None = UART_HWCONTROL_NONE,
		RTS = UART_HWCONTROL_RTS,
		CTS = UART_HWCONTROL_CTS,
		RTS_CTS = UART_HWCONTROL_RTS_CTS,
	};

	/// <summary>
	///		过采样倍率
	/// </summary>
	enum class UartOverSample
	{
		OverSample_16 = UART_OVERSAMPLING_16,

		#if defined(USART_CR1_OVER8)
		OverSample_8,
		#endif /* USART_CR1_OVER8 */
	};
}