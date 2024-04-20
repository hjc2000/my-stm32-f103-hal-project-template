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

	using UartCallbackFunc = void (*)(UART_HandleTypeDef *huart);

	/// <summary>
	///		串口抽象类。
	/// </summary>
	class Uart :public IPeripheral
	{
	protected:
		/// <summary>
		///		初始化底层的 GPIO 引脚。
		///		因为本类的派生类都是单例的，所以派生类可以定义一个静态方法，然后重写本函数，
		///		将该静态方法的函数指针返回。
		/// </summary>
		virtual UartCallbackFunc MspInitCallback() = 0;

		/// <summary>
		///		接收完成时的回调。
		///		因为本类的派生类都是单例的，所以派生类可以定义一个静态方法，然后重写本函数，
		///		将该静态方法的函数指针返回。
		/// </summary>
		/// <returns></returns>
		virtual UartCallbackFunc ReceiveCompleteCallback() = 0;

	public:
		/// <summary>
		///		派生类需要实现，返回自己的硬件串口实例。
		/// </summary>
		/// <returns></returns>
		virtual USART_TypeDef *HardwareInstance() = 0;

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
		///		初始化串口
		/// </summary>
		/// <param name="options"></param>
		void Initialize(UartInitOptions const &options);

		/// <summary>
		///		按照 UartInitOptions 的默认值进行初始化。
		/// </summary>
		void Initialize();

		/// <summary>
		///		发送完毕
		/// </summary>
		/// <returns></returns>
		bool SendingCompleted()
		{
			return (HardwareInstance()->SR & 0X40) == 0;
		}

		/// <summary>
		///		等待，直到发送完毕
		/// </summary>
		void WaitUntilSendingCompleted()
		{
			while (true)
			{
				if (SendingCompleted())
				{
					return;
				}
			}
		}

		void Send(uint8_t data)
		{
			HardwareInstance()->DR = data;
		}
	};
}
