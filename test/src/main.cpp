#include<FreeRTOS.h>
#include<TestExtiKey.h>
#include<TestIndependentWatchDog.h>
#include<TestKeyScanner.h>
#include<TestSerial.h>
#include<atk-stm32f103/bsp.h>
#include<nlohmann/json.hpp>
#include<stdexcept>
#include<string>
#include<task.h>
#include<task/Task.h>

using namespace bsp;
using namespace nlohmann;

//void TestWindowWatchDog();

int main(void)
{
	while (true)
	{
		try
		{
			BSP::Initialize();
			std::shared_ptr<task::Task> test_task = task::Task::Run([]()
			{
				std::unique_ptr<json> j{ new json{
					{"数据",12}
				} };

				BSP::Serial().Begin(115200);
				while (true)
				{
					BSP::Serial().PrintLine(j->dump(4));
					BSP::Delayer().Delay(std::chrono::seconds{ 1 });
					BSP::RedDigitalLed().Toggle();
				}
			}, 512);
			vTaskStartScheduler();
		}
		catch (std::exception const &e)
		{
			BSP::Serial().ReportError("main 函数中捕获到逃逸的 std::exception。");
			BSP::Serial().ReportError(e.what());
		}
		catch (...)
		{
			BSP::Serial().ReportError("main 函数中捕获到逃逸的未知类型的异常。");
		}
	}
}

//void TestWindowWatchDog()
//{
//	BSP_Initialize();
//	BSP_RedDigitalLed().TurnOn();
//	Delayer::Instance().Delay(std::chrono::milliseconds(1000));
//
//	WindowWatchDogInitOptions options;
//	options._counter_reload_value = 0x7f;
//	options._window_upper_bound = 0x5f;
//	options._prescaler = WindowWatchDogPrescaler::Div8;
//	options._early_wakeup_interrupt_mode = WindowWatchDogEarlyWakeupInterruptMode::Enable;
//	WindowWatchDog::Instance().Initialize(options);
//	WindowWatchDog::Instance()._on_early_wakeup_interrupt = []()
//	{
//		BSP_GreenDigitalLed().Toggle();
//	};
//
//	while (true)
//	{
//		BSP_RedDigitalLed().TurnOff();
//	}
//}
