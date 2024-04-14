#include"Exti.h"

using namespace hal;

void EXTI0_IRQHandler()
{
	ExtiInterruptHandler::Instance().HandleExti0Irq();
}

void EXTI1_IRQHandler()
{
	ExtiInterruptHandler::Instance().HandleExti1Irq();
}

void EXTI2_IRQHandler()
{
	ExtiInterruptHandler::Instance().HandleExti2Irq();
}

void EXTI3_IRQHandler()
{
	ExtiInterruptHandler::Instance().HandleExti3Irq();
}

void EXTI4_IRQHandler()
{
	ExtiInterruptHandler::Instance().HandleExti4Irq();
}
