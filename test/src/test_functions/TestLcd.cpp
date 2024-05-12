#include"TestLcd.h"
#include<atk-stm32f103/bsp.h>

void TestLcd()
{
	BSP::Initialize();
	BSP::Serial().Begin(115200);
	BSP::GreenDigitalLed().TurnOn();
	BSP::Lcd().DisplayOn();

	int i = 0;
	while (true)
	{
		BSP::Lcd().SetWindow(
			BSP::Lcd().Width() / 2,
			BSP::Lcd().Height() / 2,
			BSP::Lcd().Width() / 2,
			BSP::Lcd().Height() / 2
		);

		BSP::Lcd().Clear(static_cast<bsp::Color>(i++));
		if (i >= static_cast<int>(bsp::Color::ColorEnd))
		{
			i = 0;
		}

		BSP::RedDigitalLed().Toggle();
		BSP::Delayer().Delay(std::chrono::seconds{ 1 });
	}
}
