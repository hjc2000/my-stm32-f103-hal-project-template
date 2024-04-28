#pragma once
#include<hal-wrapper/IClockSwitchable.h>
#include<hal-wrapper/IHandleWrapper.h>
#include<hal-wrapper/IHardwareInstanceWrapper.h>
#include<hal-wrapper/peripheral/dma/IDmaChannel.h>
#include<hal-wrapper/peripheral/dma/ITxDmaLinkable.h>
#include<hal-wrapper/peripheral/uart/UartInitOptions.h>
#include<stdint.h>

namespace hal
{
	using UartCallbackFunc = void (*)(UART_HandleTypeDef *huart);

	/// <summary>
	///		串口抽象类。
	/// </summary>
	class IUart :
		public IHardwareInstanceWrapper<USART_TypeDef>,
		public ITxDmaLinkable<UART_HandleTypeDef>,
		public IClockSwitchable
	{
	public:
		#pragma region 需要派生类返回函数指针
		/// <summary>
		///		需要派生类返回一个用来初始化底层的 GPIO 引脚的函数的指针。
		/// </summary>
		virtual UartCallbackFunc MspInitCallbackFunc() = 0;

		/// <summary>
		///		需要派生类返回函数指针，用于接收完成时的回调。
		/// </summary>
		/// <returns></returns>
		virtual UartCallbackFunc ReceiveCompleteInterruptCallbackFunc() = 0;
		#pragma endregion

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

		#pragma region 直接写 DR 寄存器发送
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

		#pragma region DMA 发送
		/// <summary>
		///		派生类返回你的发送 DMA 通道实例。
		/// </summary>
		/// <returns></returns>
		virtual IDmaChannel &TxDmaChannel() = 0;

		/// <summary>
		///		为下一次 DMA 发送做准备。调用后，应该使 SendWithDma 函数有效。
		///		- 用户需要注意，不要在发送到一半时调用本函数，否则可能会终止传输。
		/// </summary>
		virtual void PerepareForNextDmaTx() = 0;

		/// <summary>
		///		使用 DMA 发送数据。
		///		- 调用后，可以使用 WaitForDmaTx 方法来等待发送完成。
		/// </summary>
		/// <param name="buffer"></param>
		/// <param name="size"></param>
		/// <returns></returns>
		HAL_StatusTypeDef SendWithDma(uint8_t const *buffer, uint16_t size)
		{
			return HAL_UART_Transmit_DMA(Handle(), buffer, size);
		}

		/// <summary>
		///		等待发送的 DMA 传输完成。
		/// </summary>
		void WaitForDmaTx();
		#pragma endregion

		/// <summary>
		///		关闭 DMA。
		///		- 会导致进行到一半的传输工作直接终止。
		///		- 会同时停止发送和接收并关闭这两个通道。
		/// </summary>
		void CloseDma()
		{
			HAL_UART_DMAStop(Handle());
		}

		#pragma region 接收
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
		///		每次在中断中接收数据后，接收中断都会被禁用，此时需要调用本函数重新启用。
		/// </summary>
		void EnableReceiveInterrupt()
		{
			HAL_UART_Receive_IT(Handle(), ReceiveBuffer(), ReceiveBufferSize());
		}
		#pragma endregion

		#pragma region ITxDmaLinkable
		DMA_HandleTypeDef *DmaTxHandle() override
		{
			return Handle()->hdmatx;
		}

		void SetDmaTxHandle(DMA_HandleTypeDef *value) override
		{
			Handle()->hdmatx = value;
		}
		#pragma endregion
	};
}
