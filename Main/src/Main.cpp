#include"Main.h"
#include"sys.h"
#include"usart.h"
#include<atk-stm32f103/Clock.h>
#include<atk-stm32f103/Led.h>
#include<hal-wrapper/GpioPort.h>
#include<hal-wrapper/Systic.h>

using namespace hal;
using namespace atk;

void Main()
{
	HAL_Init();
	config_72mhz_hclk();
	RedDigitalLed::Instance().Initialize();
	GreenDigitalLed::Instance().Initialize();

	while (1)
	{
		RedDigitalLed::Instance().SwitchOff();
		GreenDigitalLed::Instance().SwitchOn();
		Systic::NopLoopDelay(std::chrono::seconds(1));
		RedDigitalLed::Instance().SwitchOn();
		GreenDigitalLed::Instance().SwitchOff();
		Systic::NopLoopDelay(std::chrono::seconds(1));
	}
}
