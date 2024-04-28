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

	};
}
