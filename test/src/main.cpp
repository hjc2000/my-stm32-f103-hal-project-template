#include <base/math/Fraction.h>
#include <bsp-interface/test/TestIndependentWatchDog.h>
#include <bsp-interface/test/TestKeyScanner.h>
#include <bsp-interface/test/TestLcd.h>
#include <bsp-interface/test/TestSerial.h>
#include <bsp/bsp.h>
#include <stdexcept>
#include <string>
#include <task/Task.h>
#include <TestBaseTimer.h>
#include <TestExtiKey.h>

int main(void)
{
    BSP::Initialize();

    std::shared_ptr<task::Task> lvgl_init_task = task::Task::Create(
        []()
        {
            try
            {
                bsp::TestSerial();
                // TestIndependentWatchDog();
                // TestExtiKey();
                // bsp::TestLcd();
                // bsp::TestKeyScanner();
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
