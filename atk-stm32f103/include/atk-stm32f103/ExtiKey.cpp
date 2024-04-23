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




#include<atk-stm32f103/Clock.h>
#include<atk-stm32f103/Led.h>

void atk::TestExtiKey()
{
	HAL_Init();
	config_72mhz_hclk();
	RedDigitalLed::Instance().TurnOn();
	while (1)
	{
		if (ExtiKey0::Instance().IsPressed())
		{
			RedDigitalLed::Instance().Toggle();
			GreenDigitalLed::Instance().Toggle();
			ExtiKey0::Instance().ClearPressedFlag();
		}
	}
}
