#include"TestBaseTimer.h"
#include<bsp/bsp.h>

using namespace bsp;

void TestBaseTimer()
{
	BSP::Initialize();
	BSP::BaseTimer().Initialize(std::chrono::milliseconds{ 1000 });
	BSP::BaseTimer().SetPeriodElapsedCallback([]()
	{
		BSP::GreenDigitalLed().Toggle();
	});

	BSP::BaseTimer().Start();

	while (true)
	{
		BSP::RedDigitalLed().Toggle();
		BSP::Delayer().Delay(std::chrono::seconds{ 1 });
	}
}
