#pragma once
#include<hal-wrapper/peripheral/IPeripheral.h>
#include<hal-wrapper/peripheral/UartEnum.h>
#include<stdint.h>

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
		UartOverSample _over_sampling;

		operator UART_InitTypeDef() const;
	};

	class Uart :public IPeripheral
	{
		static Uart *_current_to_init;
		friend void ::HAL_UART_MspInit(UART_HandleTypeDef *huart);

	public:
		/// <summary>
		///		派生类需要实现，返回自己的硬件串口实例。
		/// </summary>
		/// <returns></returns>
		virtual USART_TypeDef &HardwareInstance() = 0;

		/// <summary>
		///		派生类需要准备接收缓冲区。本函数返回缓冲区头指针。
		/// </summary>
		/// <returns></returns>
		virtual uint8_t *ReceiveBuffer() = 0;

		/// <summary>
		///		接收缓冲区的大小。
		/// </summary>
		/// <returns></returns>
		virtual uint16_t ReceiveBufferSize() = 0;

		/// <summary>
		///		初始化底层的 GPIO 引脚。
		/// </summary>
		virtual void MspInit() = 0;

		/// <summary>
		///		初始化串口
		/// </summary>
		/// <param name="options"></param>
		void Initialize(UartInitOptions const &options);
	};
}
