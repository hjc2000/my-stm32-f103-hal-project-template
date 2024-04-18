#pragma once
#include<hal-wrapper/peripheral/IPeripheral.h>
#include<hal-wrapper/peripheral/UartEnum.h>
#include<stdint.h>

namespace hal
{
	class UartInitOptions
	{
	public:
		/// <summary>
		///		波特率
		/// </summary>
		uint32_t _baud_rate;

		/// <summary>
		///		一个串行帧有多少位
		/// </summary>
		UartWordLength _word_length;

		/// <summary>
		///		一个串行帧有多少个停止位
		/// </summary>
		UartStopBitCount _stop_bit_count;

		/// <summary>
		///		校验模式。
		///		- 校验位被放到串行帧中除了停止位以外的最高位。
		/// </summary>
		UartParity _parity;

		/// <summary>
		///		收发模式
		/// </summary>
		UartMode _mode;

		/// <summary>
		///		硬件流控
		/// </summary>
		UartHardwareFlowControl _hw_flow_ctl;

		/// <summary>
		///		过采样倍率
		/// </summary>
		uint32_t _over_sampling;              /*!< Specifies whether the Over sampling 8 is enabled or disabled, to achieve higher speed (up to fPCLK/8).
		This parameter can be a value of @ref UART_Over_Sampling. This feature is only available
		on STM32F100xx family, so OverSampling parameter should always be set to 16. */
	};

	class Uart :public IPeripheral
	{
	public:
		bool IsClockEnabled() override;
		void EnableClock() override;
		void DisableClock() override;
	};
}