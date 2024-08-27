#include <base/Initializer.h>
#include <base/math/Fraction.h>
#include <bsp-interface/di/di.h>
#include <bsp-interface/test/TestIndependentWatchDog.h>
#include <bsp-interface/test/TestLcd.h>
#include <bsp-interface/test/TestSerial.h>
#include <bsp/bsp.h>
#include <stdexcept>
#include <string>
#include <task/Task.h>
#include <test_functions.h>

using namespace bsp;

int main(void)
{
    BSP::Initialize();
    base::Initializer::Initialize();

    std::shared_ptr<task::Task> lvgl_init_task = task::Task::Create(
        []()
        {
            try
            {
                // bsp::TestSerial();
                // TestIndependentWatchDog();
                // TestExtiKey();
                TestLcd();
                // TestKeyScanner();
            }
            catch (std::exception const &e)
            {
                std::string msg = e.what();
                while (1)
                {
                }
            }
            catch (...)
            {
                while (1)
                {
                }
            }
        },
        512);

    vTaskStartScheduler();
}
