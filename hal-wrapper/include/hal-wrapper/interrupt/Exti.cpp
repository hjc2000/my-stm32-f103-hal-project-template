#include"Exti.h"

using namespace hal;

std::function<void()> Exti::_on_exti0_interrupt;
std::function<void()> Exti::_on_exti1_interrupt;
std::function<void()> Exti::_on_exti2_interrupt;
std::function<void()> Exti::_on_exti3_interrupt;
std::function<void()> Exti::_on_exti4_interrupt;

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
				if (Exti::_on_exti0_interrupt)
				{
					Exti::_on_exti0_interrupt();
				}

				break;
			}
		case GpioPin::Pin1:
			{
				if (Exti::_on_exti1_interrupt)
				{
					Exti::_on_exti1_interrupt();
				}

				break;
			}
		case GpioPin::Pin2:
			{
				if (Exti::_on_exti2_interrupt)
				{
					Exti::_on_exti2_interrupt();
				}

				break;
			}
		case GpioPin::Pin3:
			{
				if (Exti::_on_exti3_interrupt)
				{
					Exti::_on_exti3_interrupt();
				}

				break;
			}
		case GpioPin::Pin4:
			{
				if (Exti::_on_exti4_interrupt)
				{
					Exti::_on_exti4_interrupt();
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
