#include"Lcd.h"

using namespace hal;
using namespace atk;

void atk::Lcd::InitGpio()
{
	RD_Port().EnableClock();
	WR_Port().EnableClock();
	BL_Port().EnableClock();
	CS_Port().EnableClock();
	RS_Port().EnableClock();

	hal::GpioPinInitOptions gpio_init_options;
	gpio_init_options._mode = GpioPinMode::AlternateFunction_PushPull;
	gpio_init_options._pull_mode = GpioPinPull::PullUp;
	gpio_init_options._speed = GpioPinSpeed::High;
	RD_Port().InitPin(RD_Pin(), gpio_init_options);
	WR_Port().InitPin(WR_Pin(), gpio_init_options);
	CS_Port().InitPin(CS_Pin(), gpio_init_options);
	RS_Port().InitPin(RS_Pin(), gpio_init_options);

	gpio_init_options._mode = GpioPinMode::Output_PushPull;
	BL_Port().InitPin(BL_Pin(), gpio_init_options);
}
