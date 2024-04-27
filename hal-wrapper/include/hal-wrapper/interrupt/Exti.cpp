#include"Exti.h"

using namespace hal;

/// <summary>
///		EXTI 中断函数的定义。
///		* 记得在启动文件中删除这些符号的 weak 版本。
/// </summary>
extern "C"
{
	/// <summary>
	///		这里直接模仿了 HAL 库的 HAL_GPIO_EXTI_IRQHandler 函数。注意，更新 HAL 库
	///		后要记得查看 HAL_GPIO_EXTI_IRQHandler 函数是否变动。
	/// </summary>
	void EXTI0_IRQHandler()
	{
		if (!Exti::Instance().HasInterruptFlag(GpioPin::Pin0))
		{
			return;
		}

		Exti::Instance().ClearGpioInterruptPending(GpioPin::Pin0);
		if (Exti::Instance()._on_exti0_interrupt)
		{
			Exti::Instance()._on_exti0_interrupt();
		}
	}

	void EXTI1_IRQHandler()
	{
		if (!Exti::Instance().HasInterruptFlag(GpioPin::Pin1))
		{
			return;
		}

		Exti::Instance().ClearGpioInterruptPending(GpioPin::Pin1);
		if (Exti::Instance()._on_exti1_interrupt)
		{
			Exti::Instance()._on_exti1_interrupt();
		}
	}

	void EXTI2_IRQHandler()
	{
		if (!Exti::Instance().HasInterruptFlag(GpioPin::Pin2))
		{
			return;
		}

		Exti::Instance().ClearGpioInterruptPending(GpioPin::Pin2);
		if (Exti::Instance()._on_exti2_interrupt)
		{
			Exti::Instance()._on_exti2_interrupt();
		}
	}

	void EXTI3_IRQHandler()
	{
		if (!Exti::Instance().HasInterruptFlag(GpioPin::Pin3))
		{
			return;
		}

		Exti::Instance().ClearGpioInterruptPending(GpioPin::Pin3);
		if (Exti::Instance()._on_exti3_interrupt)
		{
			Exti::Instance()._on_exti3_interrupt();
		}
	}

	void EXTI4_IRQHandler()
	{
		if (!Exti::Instance().HasInterruptFlag(GpioPin::Pin4))
		{
			return;
		}

		Exti::Instance().ClearGpioInterruptPending(GpioPin::Pin4);
		if (Exti::Instance()._on_exti4_interrupt)
		{
			Exti::Instance()._on_exti4_interrupt();
		}
	}
}
