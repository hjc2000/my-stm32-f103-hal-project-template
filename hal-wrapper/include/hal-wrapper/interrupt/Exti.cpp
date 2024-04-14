#include"Exti.h"

using namespace hal;

ExtiIrqHandler *Exti::exti0_irq_handler = nullptr;
ExtiIrqHandler *Exti::exti1_irq_handler = nullptr;
ExtiIrqHandler *Exti::exti2_irq_handler = nullptr;
ExtiIrqHandler *Exti::exti3_irq_handler = nullptr;
ExtiIrqHandler *Exti::exti4_irq_handler = nullptr;

/// <summary>
///		中断处理函数。将中断处理转发到 ExtiInterruptHandler。
/// </summary>
extern "C"
{
	#pragma region 中断向量表函数
	void EXTI0_IRQHandler()
	{
		HAL_GPIO_EXTI_IRQHandler((uint32_t)GpioPin::Pin0);
	}

	void EXTI1_IRQHandler()
	{
		HAL_GPIO_EXTI_IRQHandler((uint32_t)GpioPin::Pin1);
	}

	void EXTI2_IRQHandler()
	{
		HAL_GPIO_EXTI_IRQHandler((uint32_t)GpioPin::Pin2);
	}

	void EXTI3_IRQHandler()
	{
		HAL_GPIO_EXTI_IRQHandler((uint32_t)GpioPin::Pin3);
	}

	void EXTI4_IRQHandler()
	{
		HAL_GPIO_EXTI_IRQHandler((uint32_t)GpioPin::Pin4);
	}
	#pragma endregion

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
				if (Exti::exti0_irq_handler)
				{
					Exti::exti0_irq_handler->Handle();
				}

				break;
			}
		case GpioPin::Pin1:
			{
				if (Exti::exti1_irq_handler)
				{
					Exti::exti1_irq_handler->Handle();
				}

				break;
			}
		case GpioPin::Pin2:
			{
				if (Exti::exti2_irq_handler)
				{
					Exti::exti2_irq_handler->Handle();
				}

				break;
			}
		case GpioPin::Pin3:
			{
				if (Exti::exti3_irq_handler)
				{
					Exti::exti3_irq_handler->Handle();
				}

				break;
			}
		case GpioPin::Pin4:
			{
				if (Exti::exti4_irq_handler)
				{
					Exti::exti4_irq_handler->Handle();
				}

				break;
			}
		}
	}
}
