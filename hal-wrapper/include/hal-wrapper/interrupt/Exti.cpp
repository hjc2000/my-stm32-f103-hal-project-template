#include"Exti.h"

using namespace hal;

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

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	ExtiInterruptHandler::Instance().HandleInterrupt((GpioPin)GPIO_Pin);
}
