#include <base/math/Fraction.h>
#include <base/RentedPtrFactory.h>
#include <bsp-interface/di/console.h>
#include <bsp-interface/di/serial.h>
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
            // DI_Serial().Open(*DICreate_ISerialOptions());
            // DI_Console().SetOutStream(base::RentedPtrFactory::Create(&DI_Serial()));

            bsp::TestSerial();
            // bsp::TestIndependentWatchDog();
            // TestExtiKey();
            // bsp::TestLcd();
            // bsp::TestKeyScanner();
        },
        512);

    DI_TaskManager().StartScheduler();
}
