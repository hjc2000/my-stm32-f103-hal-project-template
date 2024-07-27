#include "TestLcd.h"
#include <bsp/bsp.h>

void TestLcd()
{
	BSP::Serial().Open();
	DI_GreenDigitalLed().TurnOn();
	BSP::Lcd().DisplayOn();

	while (true)
	{
		BSP::Delayer().Delay(std::chrono::seconds{1});
		for (uint32_t x = 0; x < BSP::Lcd().Width(); x++)
		{
			for (uint32_t y = 0; y < BSP::Lcd().Height(); y++)
			{
				BSP::Lcd().DrawPoint(x, y, 0x07E0);
			}
		}

		BSP::Delayer().Delay(std::chrono::seconds{1});
		BSP::Lcd().Clear(bsp::Color::Black);
		DI_RedDigitalLed().Toggle();
		BSP::Delayer().Delay(std::chrono::seconds{1});
	}
}
