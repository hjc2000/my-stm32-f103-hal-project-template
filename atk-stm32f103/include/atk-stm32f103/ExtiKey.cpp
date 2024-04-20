#include"ExtiKey.h"

using namespace atk;
using namespace hal;

void atk::ExtiKey0::Deinitialize()
{
	Exti::_exti4_irq_handler = nullptr;
	Interrupt::DisableIRQ(IRQn_Type::EXTI4_IRQn);
}

void atk::ExtiKey0::HandleExtiIrq()
{
	Systic::NopLoopDelay(std::chrono::milliseconds(20));
	_is_pressed = !Port().DigitalReadPin(Pin());
	Exti::ClearGpioInterruptPending(Pin());
}
