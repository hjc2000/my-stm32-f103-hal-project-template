#pragma once
#include<hal-wrapper/peripheral/GpioPort.h>

namespace hal
{
	class ExtiInterruptHandler
	{
	protected:
		ExtiInterruptHandler() = default;

	public:
		static ExtiInterruptHandler &Instance()
		{
			static ExtiInterruptHandler instance;
			if (_custom_handler != nullptr)
			{
				return *_custom_handler;
			}

			return instance;
		}

		/// <summary>
		///		初始时为空指针。通过赋值为自定义的 ExtiInterruptHandler 对象
		///		的指针，可以改变 Instance 函数所返回的实例，从而实现自定义中断处理函数逻辑。
		/// </summary>
		static ExtiInterruptHandler *_custom_handler;

		/// <summary>
		///		发生中断时会被回调。
		/// </summary>
		/// <param name="pin">
		///		中断来自哪个 EXTI 的线，会利用 GpioPin 枚举值来表示。
		/// </param>
		virtual void HandleInterrupt(GpioPin pin) {}
	};
}