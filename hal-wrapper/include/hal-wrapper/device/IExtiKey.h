#pragma once
#include<hal-wrapper/device/IDevice.h>
#include<hal-wrapper/interrupt/Exti.h>

namespace hal
{
	/// <summary>
	///		本类依赖一个在中断函数和主程序中传递的信号。这个信号如果是你自己定义的一个变量，
	///		而不是借助 freertos 的信号量之类的，需要注意标记为 volatile。
	/// </summary>
	class IExtiKey :
		public IDevice,
		public ExtiIrqHandler
	{
	public:
		/// <summary>
		///		返回 true 表示按键被按下了。
		///		不应该在中断中处理按键的事务，应该在中断中设置一个信号，到主程序中接收信号，
		///		然后才处理按键的事务。因为中断函数应该尽可能精简，耗时少。
		/// </summary>
		/// <returns></returns>
		virtual bool IsPressed() const = 0;

		/// <summary>
		///		清除用来表示按钮被按下的标志。清除后，IsPressed 方法应该返回 false。
		/// </summary>
		virtual void ClearPressedFlag() = 0;
	};
}