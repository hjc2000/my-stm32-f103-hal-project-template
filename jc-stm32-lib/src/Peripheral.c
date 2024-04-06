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
	}
}
