#include<FreeRTOS.h>
#include<TestExtiKey.h>
#include<TestIndependentWatchDog.h>
#include<TestKeyScanner.h>
#include<atk-stm32f103/bsp.h>
#include<stdexcept>
#include<string>
#include<task.h>

using namespace bsp;

void TestUart1();
//void TestWindowWatchDog();

void startup_task(void *param)
{
	//TestKeyScanner();
	//TestExtiKey();
	TestUart1();
	//TestIndependentWatchDog();
	//TestWindowWatchDog();
}

int main(void)
{
	while (true)
	{
		try
		{
			BSP::Initialize();

			// usStackDepth 参数的单位不是字节，而是字。32 位 CPU 一个字是 4 字节。
			xTaskCreate(
				startup_task,
				"startup_task",
				128,
				nullptr,
				1,
				nullptr
			);

			vTaskStartScheduler();
		}
		catch (...)
		{

		}
	}
}

void TestUart1()
{
	BSP::RedDigitalLed().TurnOn();
	BSP::Serial().Begin(115200);

	while (1)
	{
		BSP::Delayer().Delay(std::chrono::seconds(1));
		BSP::Serial().Print("hello world\n");
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
