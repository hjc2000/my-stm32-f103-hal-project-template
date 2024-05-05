#include<atk-stm32f103/bsp.h>
#include<bsp-interface/EndianConverter.h>
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
			std::shared_ptr<task::Task> test_serial_task = task::Task::Create([]()
			{
				BSP::Initialize();
				BSP::Lcd().TurnOnBackLight();
				//BSP::Serial().Begin(115200);
				while (true)
				{
					//BSP::Lcd().WriteCommand(0XD3);

					//uint16_t id = BSP::Lcd().ReadData();
					//bsp::EndianConverter::ToBigEndian(reinterpret_cast<uint8_t *>(id), 2, 2);
					//BSP::Serial().Write(reinterpret_cast<uint8_t *>(id), 0, 2);

					//id = BSP::Lcd().ReadData();
					//bsp::EndianConverter::ToBigEndian(reinterpret_cast<uint8_t *>(id), 2, 2);
					//BSP::Serial().Write(reinterpret_cast<uint8_t *>(id), 0, 2);

					//id = BSP::Lcd().ReadData();
					//bsp::EndianConverter::ToBigEndian(reinterpret_cast<uint8_t *>(id), 2, 2);
					//BSP::Serial().Write(reinterpret_cast<uint8_t *>(id), 0, 2);

					//id = BSP::Lcd().ReadData();
					//bsp::EndianConverter::ToBigEndian(reinterpret_cast<uint8_t *>(id), 2, 2);
					//BSP::Serial().Write(reinterpret_cast<uint8_t *>(id), 0, 2);

					BSP::RedDigitalLed().Toggle();
					BSP::Delayer().Delay(std::chrono::milliseconds{ 1000 });
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
