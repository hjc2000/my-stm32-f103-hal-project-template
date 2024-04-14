#pragma once
#include<hal-wrapper/peripheral/GpioPort.h>

namespace hal
{
	class ExtiIrqHandler
	{
	public:
		virtual void Handle() = 0;
	};

	class Exti
	{
		Exti() = delete;

	public:
		/// <summary>
		///		清除某个 GPIO 引脚上的中断挂起标志。
		///		- 所有 GPIO 端口的 pin0 连接到中断管理器的第 line0，
		///		  所有 GPIO 端口的 pin1 连接到中断管理器的第 line1，
		///		  以此类推。
		///		- 例如同样都是 pin0，可能来自 GPIOA，GPIOB,...... 等。所有
		///		  这些端口的 pin0 都通过一个多路选择开关连接到中断管理器的 line0 上，
		///		  这个多路选择开关只能同时选择一条路导通。
		///		- 这里的清除某个引脚上的中断挂起标志其实应该说是清除某个 line 上的中断挂起标志。
		///		  只不过这些 line 刚好跟 GpioPin 枚举值一一对应而已。
		///		- 所谓中断挂起标志就是表示发生了中断，但是中断服务程序还没被执行。可能是因为禁用了
		///		  中断。
		/// </summary>
		/// <param name="pin"></param>
		static void ClearGpioInterruptPending(GpioPin pin)
		{
			__HAL_GPIO_EXTI_CLEAR_IT((uint32_t)pin);
		}

		#pragma region 回调函数
		/* 这里使用的是 std::function，他有可能引起动态内存分配。
		* 所以不要多次赋值，最好是初始化赋值一次后就永远不变，除非复位。
		*/

		static ExtiIrqHandler *exti0_irq_handler;
		static ExtiIrqHandler *exti1_irq_handler;
		static ExtiIrqHandler *exti2_irq_handler;
		static ExtiIrqHandler *exti3_irq_handler;
		static ExtiIrqHandler *exti4_irq_handler;
		#pragma endregion

	};
}
