#include"Exti.h"
#include<stm32f1xx_it.h>

using namespace hal;

Exti::Exti()
{
	g_on_exti0_interrupt = []()
	{
		HAL_GPIO_EXTI_IRQHandler((uint32_t)GpioPin::Pin0);
	};

	g_on_exti1_interrupt = []()
	{
		HAL_GPIO_EXTI_IRQHandler((uint32_t)GpioPin::Pin1);
	};

	g_on_exti2_interrupt = []()
	{
		HAL_GPIO_EXTI_IRQHandler((uint32_t)GpioPin::Pin2);
	};

	g_on_exti3_interrupt = []()
	{
		HAL_GPIO_EXTI_IRQHandler((uint32_t)GpioPin::Pin3);
	};

	g_on_exti4_interrupt = []()
	{
		HAL_GPIO_EXTI_IRQHandler((uint32_t)GpioPin::Pin4);
	};
}

/// <summary>
///		中断处理函数。将中断处理转发到 ExtiInterruptHandler。
/// </summary>
extern "C"
{
	/// <summary>
	///		覆盖 hal 中的 weak 版本。
	/// </summary>
	/// <param name="GPIO_Pin"></param>
	void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
	{
		switch ((GpioPin)GPIO_Pin)
		{
		case GpioPin::Pin0:
			{
				if (Exti::Instance()._on_exti0_interrupt)
				{
					Exti::Instance()._on_exti0_interrupt();
				}

				break;
			}
		case GpioPin::Pin1:
			{
				if (Exti::Instance()._on_exti1_interrupt)
				{
					Exti::Instance()._on_exti1_interrupt();
				}

				break;
			}
		case GpioPin::Pin2:
			{
				if (Exti::Instance()._on_exti2_interrupt)
				{
					Exti::Instance()._on_exti2_interrupt();
				}

				break;
			}
		case GpioPin::Pin3:
			{
				if (Exti::Instance()._on_exti3_interrupt)
				{
					Exti::Instance()._on_exti3_interrupt();
				}

				break;
			}
		case GpioPin::Pin4:
			{
				if (Exti::Instance()._on_exti4_interrupt)
				{
					Exti::Instance()._on_exti4_interrupt();
				}

				break;
			}
		default:
			{
				break;
			}
		}
	}
}
