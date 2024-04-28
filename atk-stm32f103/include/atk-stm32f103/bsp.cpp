#include"bsp.h"
#include<AtkExtiKey.h>
#include<AtkKey.h>
#include<Delayer.h>
#include<DigitalLed.h>
#include<FreeRTOS.h>
#include<atomic>
#include<bsp-interface/KeyScanner.h>
#include<functional>
#include<hal-wrapper/clock/Osc.h>
#include<hal-wrapper/clock/Systic.h>
#include<hal-wrapper/clock/clock-signal/ClockSignal.h>
#include<hal-wrapper/peripheral/independent-watch-dog/IndependentWatchDog.h>
#include<task.h>

using namespace hal;
using namespace atk;

void config_clock_source()
{
	OscInitOptions osc_init_options;
	osc_init_options._oscillator_type = OscillatorType::HSE;
	osc_init_options._hse_state = HseState::On;
	osc_init_options._hse_prediv = HsePrediv::DIV1;
	osc_init_options._pll_init_options._state = PllState::On;
	osc_init_options._pll_init_options._clock_source = PllClockSource::HSE;
	osc_init_options._pll_init_options._mul = PllMul::Mul9;
	if (Osc::Config(osc_init_options) != HAL_OK)
	{
		/* 时钟初始化失败，之后的程序将可能无法正常执行，可以在这里加入自己的处理 */
		while (1);
	}
}

void config_clock_signal()
{
	ClockSignalInitOptions clock_init_options;
	clock_init_options._clock_type = ClockType::SYSCLK
		| ClockType::HCLK
		| ClockType::PCLK1
		| ClockType::PCLK2;

	clock_init_options._sysclk_source = SysclkSource::PLLCLK;
	clock_init_options._ahb_clk_divider = AHBDivider::DIV1;
	clock_init_options._apb1_divider = APBDivider::DIV2;
	clock_init_options._apb2_divider = APBDivider::DIV1;
	if (ClockSignal::Config(clock_init_options, FlashLatency::Latency2) != HAL_OK)
	{
		/* 时钟初始化失败，之后的程序将可能无法正常执行，可以在这里加入自己的处理 */
		while (1);
	}
}

void BSP::Initialize()
{
	HAL_Init();
	config_clock_source();
	config_clock_signal();
	hal::Systic::SetClockSource(hal::SysticClockSource::HCLK_DIV8);
}

void BSP::SystemReset()
{
	Interrupt::SystemReset();
}

bsp::IDelayer &BSP::Delayer()
{
	return hal::Delayer::Instance();
}

bsp::IIndependentWatchDog &BSP::IndependentWatchDog()
{
	return hal::IndependentWatchDog::Instance();
}

bsp::IDigitalLed &BSP::RedDigitalLed()
{
	return RedDigitalLed::Instance();
}

bsp::IDigitalLed &BSP::GreenDigitalLed()
{
	return GreenDigitalLed::Instance();
}

bsp::IKeyScanner &BSP::KeyScanner()
{
	static std::atomic_bool initialized = false;
	static std::vector<bsp::IKey *> keys{ (size_t)KeyIndex::EnumEndFlag };
	if (!initialized)
	{
		keys[(uint16_t)KeyIndex::Key0] = &Key0::Instance();
		keys[(uint16_t)KeyIndex::Key1] = &Key1::Instance();
	}

	static bsp::KeyScanner key_scanner{ keys, hal::Delayer::Instance() };

	// 初始化完成
	initialized = true;
	return key_scanner;
}

bsp::IEventDrivenKey &BSP::WakeUpKey()
{
	return ExtiKey0::Instance();
}

extern "C"
{
	extern void xPortSysTickHandler();

	void SysTick_Handler()
	{
		HAL_IncTick();
		if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
		{
			xPortSysTickHandler();
		}
	}
}
