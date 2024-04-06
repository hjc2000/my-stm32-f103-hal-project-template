#include"Peripheral.h"

uint8_t peripheral_clock_enabled(Peripheral p)
{
	switch (p)
	{
	case Peripheral_GPIO_A:
		{
			return __HAL_RCC_GPIOA_IS_CLK_ENABLED();
		}
	case Peripheral_GPIO_B:
		{
			return __HAL_RCC_GPIOB_IS_CLK_ENABLED();
		}
	case Peripheral_GPIO_C:
		{
			return __HAL_RCC_GPIOC_IS_CLK_ENABLED();
		}
	case Peripheral_GPIO_D:
		{
			return __HAL_RCC_GPIOD_IS_CLK_ENABLED();
		}
	case Peripheral_ADC1:
		{
			return __HAL_RCC_ADC1_IS_CLK_ENABLED();
		}

		#ifdef HAS_ADC2
	case Peripheral_ADC2:
		{
			return __HAL_RCC_ADC2_IS_CLK_ENABLED();
		}
		#endif // HAS_ADC2

	default:
		{
			return 0;
		}
	}
}

uint8_t peripheral_clock_disabled(Peripheral p)
{
	return !peripheral_clock_enabled(p);
}

void peripheral_enable_clock(Peripheral p)
{
	switch (p)
	{
	case Peripheral_GPIO_A:
		{
			__HAL_RCC_GPIOA_CLK_ENABLE();
		}
	case Peripheral_GPIO_B:
		{
			__HAL_RCC_GPIOB_CLK_ENABLE();
		}
	case Peripheral_GPIO_C:
		{
			__HAL_RCC_GPIOC_CLK_ENABLE();
		}
	case Peripheral_GPIO_D:
		{
			__HAL_RCC_GPIOD_CLK_ENABLE();
		}
	case Peripheral_ADC1:
		{
			__HAL_RCC_ADC1_CLK_ENABLE();
		}

		#ifdef HAS_ADC2
	case Peripheral_ADC2:
		{
			__HAL_RCC_ADC2_CLK_ENABLE();
		}
		#endif // HAS_ADC2
	}
}
