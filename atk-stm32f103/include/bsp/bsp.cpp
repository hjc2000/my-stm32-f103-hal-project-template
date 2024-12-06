#include "bsp.h"
#include <AtkKey.h>
#include <atomic>
#include <base/RentedPtrFactory.h>
#include <bsp-interface/di/delayer.h>
#include <bsp-interface/di/led.h>
#include <DigitalLed.h>
#include <ExtiWakeUpKey.h>
#include <FreeRTOS.h>
#include <functional>
#include <hal-wrapper/clock/clock-signal-config/ClockSignalConfig.h>
#include <hal-wrapper/clock/ClockSignal.h>
#include <hal-wrapper/clock/ConfigClockSignal.h>
#include <hal-wrapper/clock/Osc.h>
#include <hal-wrapper/peripheral/window-watch-dog/WindowWatchDog.h>
#include <Lcd.h>
#include <task.h>

using namespace bsp;
using namespace hal;

void BSP::Initialize()
{
    auto config_clock_source = []()
    {
        OscConfig osc_init_options;
        osc_init_options._oscillator_type = OscConfig::OscillatorType::HSE;
        osc_init_options._hse_state = OscConfig::HseState::On;
        osc_init_options._hse_prediv = OscConfig::HsePrediv::DIV1;
        osc_init_options._pll_init_options._state = PllState::On;
        osc_init_options._pll_init_options._clock_source = PllClockSource::HSE;
        osc_init_options._pll_init_options._mul = PllMul::Mul9;
        Osc::SetConfig(osc_init_options);
    };

    // 开启 FPU。这个是针对 H7 系列的。
    SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));

    // HAL_Init 函数已经将中断优先级分组设置为 4 了。
    HAL_Init();
    config_clock_source();
    ConfigClockSignal();
}

bsp::IEventDrivenKey &BSP::WakeUpKey()
{
    return bsp::ExtiWakeUpKey::Instance();
}

void TestWindowWatchDog()
{
    DI_Delayer().Delay(std::chrono::seconds{1});
    DI_RedDigitalLed().TurnOn();

    hal::WindowWatchDogConfig config;
    config.SetCounterReloadValue(0x7f);
    config.SetWindow(0x5f);
    config.SetPrescaler(hal::WindowWatchDogConfig::PrescalerOption::DIV2);
    config.SetEarlyWakeupInterrupt(hal::WindowWatchDogConfig::EarlyWakeupInterruptOption::Enable);

    hal::WindowWatchDog::Instance().SetEarlyWakeupInterruptCallback(
        [&]()
        {
            DI_GreenDigitalLed().Toggle();
        });

    hal::WindowWatchDog::Instance().Initialize(config);

    while (true)
    {
        DI_RedDigitalLed().Toggle();
        DI_Delayer().Delay(std::chrono::seconds{1});
    }
}
