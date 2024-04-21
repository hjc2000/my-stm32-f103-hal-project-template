#pragma once
#include<hal-wrapper/IHandleWrapper.h>
#include<hal-wrapper/peripheral/IPeripheral.h>
#include<hal-wrapper/peripheral/dma/IDmaLinkable.h>
#include<hal-wrapper/peripheral/uart/UartInitOptions.h>
#include<hal-wrapper/peripheral/uart/UartReceiveCompletedHandler.h>
#include<stdint.h>

namespace hal
{
	/// <summary>
	///		串口抽象类。
	/// </summary>
	class Uart :
		public IPeripheral<USART_TypeDef>,
		public IDmaLinkable<UART_HandleTypeDef>
	{
		UART_HandleTypeDef _handle;

	protected:
		/// <summary>
		///		需要派生类返回一个用来初始化底层的 GPIO 引脚的函数的指针。
		/// </summary>
		virtual UartCallbackFunc MspInitCallback() = 0;

		/// <summary>
		///		需要派生类返回函数指针，用于接收完成时的回调。
		/// </summary>
		/// <returns></returns>
		virtual UartCallbackFunc ReceiveCompleteCallback() = 0;

	public:
		/// <summary>
		///		派生类需要实现，返回自己的硬件串口实例。
		/// </summary>
		/// <returns></returns>
		virtual USART_TypeDef *HardwareInstance() override = 0;

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

		#pragma region 初始化
		/// <summary>
		///		初始化串口
		/// </summary>
		/// <param name="options"></param>
		void Initialize(UartInitOptions const &options);

		/// <summary>
		///		按照 UartInitOptions 的默认值进行初始化。
		/// </summary>
		void Initialize();
		#pragma endregion

		#pragma region 发送
		/// <summary>
		///		发送完毕
		/// </summary>
		/// <returns></returns>
		bool SendCompleted()
		{
			return (HardwareInstance()->SR & 0X40) != 0;
		}

		/// <summary>
		///		等待，直到发送完毕
		/// </summary>
		void WaitUntilSendCompleted()
		{
			while (true)
			{
				if (SendCompleted())
				{
					return;
				}
			}
		}

		/// <summary>
		///		写发送寄存器 DR。
		///		本函数不保证发送寄存器的数据已经被发送完了。
		/// </summary>
		/// <param name="data"></param>
		void WriteDR(uint8_t data)
		{
			HardwareInstance()->DR = data;
		}

		/// <summary>
		///		写发送寄存器 DR。不过本函数会等待，直到上一次的数据发送完。
		/// </summary>
		/// <param name="data"></param>
		void WriteDR_WithWaiting(uint8_t data)
		{
			WaitUntilSendCompleted();
			WriteDR(data);
		}
		#pragma endregion

		#pragma region 接收
		/// <summary>
		///		每次在中断中接收数据后，接收中断都会被禁用，此时需要调用本函数重新启用。
		/// </summary>
		void EnableReceiveInterrupt()
		{
			HAL_UART_Receive_IT(&_handle, ReceiveBuffer(), ReceiveBufferSize());
		}
		#pragma endregion

		/// <summary>
		///		接收完成时被回调
		/// </summary>
		void(*_on_receive_completed)() = nullptr;
		UartReceiveCompletedHandler *_receive_completed_handler = nullptr;

		#pragma region IDmaLinkable
		UART_HandleTypeDef *Handle() override
		{
			return &_handle;
		}

		virtual DMA_HandleTypeDef *DmaTxHandle() const override
		{
			return _handle.hdmatx;
		}
		virtual void SetDmaTxHandle(DMA_HandleTypeDef *value) override
		{
			_handle.hdmatx = value;
		}

		virtual DMA_HandleTypeDef *DmaRxHandle() const override
		{
			return _handle.hdmarx;
		}
		virtual void SetDmaRxHandle(DMA_HandleTypeDef *value) override
		{
			_handle.hdmarx = value;
		}
		#pragma endregion
	};
}
