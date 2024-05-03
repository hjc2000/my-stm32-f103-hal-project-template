#include"TestJson.h"
#include<atk-stm32f103/bsp.h>
#include<nlohmann/json.hpp>
#include<task/Task.h>

using namespace nlohmann;

void TestJson()
{
	json j{
		{"数据",12}
	};
	BSP::Serial().Begin(115200);
	while (true)
	{
		BSP::Serial().PrintLine(j.dump(4));
		BSP::Delayer().Delay(std::chrono::seconds{ 1 });
		BSP::RedDigitalLed().Toggle();
	}
}
