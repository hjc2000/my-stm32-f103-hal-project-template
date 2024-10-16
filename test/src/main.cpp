#include <base/math/Fraction.h>
#include <bsp-interface/di/task.h>
#include <bsp-interface/test/TestIndependentWatchDog.h>
#include <bsp-interface/test/TestKeyScanner.h>
#include <bsp-interface/test/TestLcd.h>
#include <bsp-interface/test/TestSerial.h>
#include <bsp/bsp.h>
#include <stdexcept>
#include <string>
#include <TestBaseTimer.h>
#include <TestExtiKey.h>

int main(void)
{
    BSP::Initialize();

    DI_TaskManager().Create(
        []()
        {
            try
            {
                bsp::TestSerial();
                // bsp::TestIndependentWatchDog();
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

    DI_TaskManager().StartScheduler();
}
