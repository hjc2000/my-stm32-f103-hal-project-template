#pragma once

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

		virtual void HandleExti0Irq() {}
		virtual void HandleExti1Irq() {}
		virtual void HandleExti2Irq() {}
		virtual void HandleExti3Irq() {}
		virtual void HandleExti4Irq() {}
	};
}