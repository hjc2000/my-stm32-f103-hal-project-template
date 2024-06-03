#pragma once
#include<functional>
#include<GpioPort.h>

extern "C"
{
	void HAL_GPIO_EXTI_Callback(uint16_t pin);
}

namespace bsp
{
	/// <summary>
	///		本类不提供开启中断的功能。设置好回调函数后，需要用 Interrupt 类来开启
	///		EXTI 中断。
	/// </summary>
	class Exti
	{
	private:
		Exti() = default;
		friend void ::HAL_GPIO_EXTI_Callback(uint16_t pin);

		std::function<void()> _on_exti0_interrupt;
		std::function<void()> _on_exti1_interrupt;
		std::function<void()> _on_exti2_interrupt;
		std::function<void()> _on_exti3_interrupt;
		std::function<void()> _on_exti4_interrupt;


	public:
		static Exti &Instance()
		{
			static Exti o;
			return o;
		}

		/// <summary>
		///		使用一条外部中断线。
		/// </summary>
		/// <param name="callback"></param>
		/// <param name="pin"></param>
		void UseLine(std::function<void()> callback, GpioPin pin);

		/// <summary>
		///		取消使用一条外部中断线。
		///		* 会先禁用对应的线的中断，然后将回调函数设为 nullptr。
		/// </summary>
		/// <param name="pin"></param>
		void UnuseLine(GpioPin pin);
	};
}
