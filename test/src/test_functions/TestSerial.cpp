#include"TestSerial.h"
#include<atk-stm32f103/bsp.h>

void TestSerial()
{
	BSP::RedDigitalLed().TurnOn();
	BSP::Serial().Begin(115200);

	while (1)
	{
		BSP::Delayer().Delay(std::chrono::seconds(1));
		BSP::Serial().Print("测试文本\n");
	}
}
