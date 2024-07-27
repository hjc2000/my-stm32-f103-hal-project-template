#include <base/math/Fraction.h>
#include <bsp-interface/test/TestLcd.h>
#include <bsp/bsp.h>
#include <stdexcept>
#include <string>
#include <task/Task.h>
#include <test_functions.h>

using namespace bsp;

int main(void)
{
	while (true)
	{
		try
		{
			BSP::Initialize();

			std::shared_ptr<task::Task> lvgl_init_task = task::Task::Create(
				[]()
				{
					// TestSerial();
					// TestKeyScanner();
					TestLcd();
				},
				512);

			vTaskStartScheduler();
		}
		catch (std::exception const &e)
		{
			DI_RedDigitalLed().TurnOff();
			BSP::Console().WriteError("main 函数中捕获到逃逸的 std::exception。");
			BSP::Console().WriteError(e.what());
		}
		catch (...)
		{
			DI_RedDigitalLed().TurnOff();
			BSP::Console().WriteError("main 函数中捕获到逃逸的未知类型的异常。");
		}
	}
}
