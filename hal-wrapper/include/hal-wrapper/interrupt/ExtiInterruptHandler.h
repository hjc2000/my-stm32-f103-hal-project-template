#pragma once
#include<hal-wrapper/peripheral/GpioPort.h>

namespace hal
{
	class ExtiInterruptHandler
	{
		ExtiInterruptHandler() = default;

	public:
		static ExtiInterruptHandler &Instance()
		{
			static ExtiInterruptHandler instance;
			if (custom_handler != nullptr)
			{
				return *custom_handler;
			}

			return instance;
		}

		/// <summary>
		///		初始时为空指针。通过赋值为自定义的 ExtiInterruptHandler 对象
		///		的指针，可以改变 Instance 函数所返回的实例，从而实现自定义中断处理函数逻辑。
		/// </summary>
		static ExtiInterruptHandler *custom_handler;

		/// <summary>
		///		发生中断时会被回调。
		/// </summary>
		/// <param name="pin">
		///		中断来自哪个 EXTI 的线，会利用 GpioPin 枚举值来表示。
		///		- 例如传入 GpioPin::Pin0 表示 EXTI 的 line0 发生了中断。
		///		  这么做是因为 pin 和 line 就是一一对应的，无论来自哪个地方的
		///		  pin0 都会接到 line0 上。
		/// </param>
		virtual void HandleInterrupt(GpioPin pin) {}
	};
}