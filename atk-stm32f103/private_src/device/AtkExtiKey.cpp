#include"AtkExtiKey.h"

using namespace atk;
using namespace hal;

ExtiKey0::ExtiKey0()
{
	// 配置引脚
	GpioPinInitOptions options;
	options._mode = GpioPinMode::Interrupt_FallingEdgeTrigger;
	options._pull_mode = GpioPinPull::PullUp;
	options._speed = GpioPinSpeed::High;

	Exti::Instance().UseLine([&]()
	{
		// 这是在中断函数中，禁止使用 Delayer 进行延时。
		Systic::NopLoopDelay(std::chrono::milliseconds(20));
		_is_pressed = !Port().DigitalReadPin(Pin());
		Exti::Instance().ClearGpioInterruptPending(Pin());
	},
		Port(),
		Pin(),
		options
	);
}
