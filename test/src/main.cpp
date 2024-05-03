#include<FreeRTOS.h>
#include<TestExtiKey.h>
#include<TestIndependentWatchDog.h>
#include<TestKeyScanner.h>
#include<TestSerial.h>
#include<atk-stm32f103/bsp.h>
#include<stdexcept>
#include<string>
#include<task.h>
#include<task/Task.h>

using namespace bsp;

//void TestWindowWatchDog();

int main(void)
{
	while (true)
	{
		try
		{
			BSP::Initialize();
			task::Task::Run(TestExtiKey);
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
