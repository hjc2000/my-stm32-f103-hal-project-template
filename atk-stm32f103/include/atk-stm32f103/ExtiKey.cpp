#include"ExtiKey.h"

using namespace atk;
using namespace hal;

void atk::ExtiKey0::Initialize()
{
	Exti::_exti4_irq_handler = this;

	// 配置引脚
	Port().EnableClock();
	GpioPinOptions options;
	options._mode = GpioPinMode::Interrupt_FallingEdgeTrigger;
	options._pull_mode = GpioPinPull::PullUp;
	options._speed = GpioPinSpeed::High;
	Port().InitPin(Pin(), options);

	// 配置好引脚模式后开中断
	Interrupt::SetPriority(IRQn_Type::EXTI4_IRQn, 0, 2);
	Interrupt::EnableIRQ(IRQn_Type::EXTI4_IRQn);
}

void atk::ExtiKey0::Deinitialize()
{
	Exti::_exti4_irq_handler = nullptr;
	Interrupt::DisableIRQ(IRQn_Type::EXTI4_IRQn);
}

void atk::ExtiKey0::Handle()
{
	Systic::NopLoopDelay(std::chrono::milliseconds(20));
	_is_pressed = !Port().DigitalReadPin(Pin());
	Exti::ClearGpioInterruptPending(Pin());
}
