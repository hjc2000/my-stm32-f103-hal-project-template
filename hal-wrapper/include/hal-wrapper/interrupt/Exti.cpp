#include"Exti.h"
#include<stm32f1xx_it.h>

using namespace hal;

Exti::Exti()
{
	/* 这里直接模仿了 HAL 库的 HAL_GPIO_EXTI_IRQHandler 函数。注意，更新 HAL 库
	* 后要记得查看 HAL_GPIO_EXTI_IRQHandler 函数是否变动。
	*/
	g_on_exti0_interrupt = [this]()
	{
		if (!HasInterruptFlag(GpioPin::Pin0))
		{
			return;
		}

		ClearGpioInterruptPending(GpioPin::Pin0);
		if (_on_exti0_interrupt)
		{
			_on_exti0_interrupt();
		}
	};

	g_on_exti1_interrupt = [this]()
	{
		if (!HasInterruptFlag(GpioPin::Pin1))
		{
			return;
		}

		ClearGpioInterruptPending(GpioPin::Pin1);
		if (_on_exti1_interrupt)
		{
			_on_exti1_interrupt();
		}
	};

	g_on_exti2_interrupt = [this]()
	{
		if (!HasInterruptFlag(GpioPin::Pin2))
		{
			return;
		}

		ClearGpioInterruptPending(GpioPin::Pin2);
		if (_on_exti2_interrupt)
		{
			_on_exti2_interrupt();
		}
	};

	g_on_exti3_interrupt = [this]()
	{
		if (!HasInterruptFlag(GpioPin::Pin3))
		{
			return;
		}

		ClearGpioInterruptPending(GpioPin::Pin3);
		if (_on_exti3_interrupt)
		{
			_on_exti3_interrupt();
		}
	};

	g_on_exti4_interrupt = [this]()
	{
		if (!HasInterruptFlag(GpioPin::Pin4))
		{
			return;
		}

		ClearGpioInterruptPending(GpioPin::Pin4);
		if (_on_exti4_interrupt)
		{
			_on_exti4_interrupt();
		}
	};
}
