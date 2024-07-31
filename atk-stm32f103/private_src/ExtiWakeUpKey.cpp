#include "ExtiWakeUpKey.h"
#include <base/Initializer.h>
#include <bsp-interface/di.h>

using namespace bsp;
using namespace hal;

static base::Initializer _init{
	[]()
	{
		bsp::ExtiWakeUpKey::Instance();
	}};

ExtiWakeUpKey::ExtiWakeUpKey()
{
	// 配置引脚
	Port().EnableClock();
	GpioPinConfig options;
	options.SetPin(Pin());
	options.SetMode(hal::GpioPinConfig::ModeOption::Interrupt_RisingEdgeTrigger);
	options.SetPull(hal::GpioPinConfig::PullOption::PullDown);
	options.SetSpeed(hal::GpioPinConfig::SpeedOption::High);
	Port().InitPin(options);
	DI_ExtiManager().Register(
		0,
		[&]()
		{
			// 这是在中断函数中，禁止使用 Delayer 进行延时。
			hal::SysTickClock::Instance().Delay(std::chrono::milliseconds{20});
			_is_pressed = Port().DigitalReadPin(Pin());
		});
}
