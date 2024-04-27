#include"AtkExtiKey.h"

using namespace atk;
using namespace hal;

ExtiKey0::ExtiKey0()
{
	Exti::Instance()._on_exti4_interrupt = [this]()
	{
		Systic::NopLoopDelay(std::chrono::milliseconds(20));
		_is_pressed = !Port().DigitalReadPin(Pin());
		Exti::Instance().ClearGpioInterruptPending(Pin());
	};

	// 配置引脚
	Port().EnableClock();
	GpioPinInitOptions options;
	options._mode = GpioPinMode::Interrupt_FallingEdgeTrigger;
	options._pull_mode = GpioPinPull::PullUp;
	options._speed = GpioPinSpeed::High;
	Port().InitPin(Pin(), options);

	// 配置好引脚模式后开中断
	Interrupt::SetPriority(IRQn_Type::EXTI4_IRQn, 0, 2);
	Interrupt::EnableIRQ(IRQn_Type::EXTI4_IRQn);
}
