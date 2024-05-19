#include<atk-stm32f103/bsp.h>
#include<bsp-interface/EndianConverter.h>
#include<lvgl/lvgl.h>
#include<stdexcept>
#include<string>
#include<task/Task.h>
#include<test_functions.h>

using namespace bsp;

//void TestWindowWatchDog();

int main(void)
{
	while (true)
	{
		try
		{
			BSP::Initialize();
			BSP::BaseTimer().Initialize(std::chrono::milliseconds{ 1 });
			BSP::BaseTimer().SetPeriodElapsedCallback([]()
			{
				lv_tick_inc(1);
			});

			BSP::BaseTimer().Start();

			std::shared_ptr<task::Task> test_serial_task = task::Task::Create([]()
			{
				TestLcd();
			}, 1024);

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
