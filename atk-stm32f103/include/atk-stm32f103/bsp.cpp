#include"bsp.h"
#include<AtkKey.h>
#include<atomic>
#include<BaseTimer1.h>
#include<bsp-interface/KeyScanner.h>
#include<ClockSignal.h>
#include<Delayer.h>
#include<DigitalLed.h>
#include<ExtiWakeUpKey.h>
#include<FreeRTOS.h>
#include<functional>
#include<IndependentWatchDog.h>
#include<Lcd.h>
#include<Osc.h>
#include<Serial.h>
#include<Systic.h>
#include<task.h>

using namespace bsp;

void BSP::Initialize()
{
	// 开启 FPU。这个是针对 H7 系列的。
	SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));

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

	auto config_clock_signal = []()
	{
		Systic::SetClockSource(SysticClockSource::HCLK_DIV8);

		ClockSignalConfig clock_init_options { };
		clock_init_options._clock_type = ClockSignalConfig::ClockType::SYSCLK
			| ClockSignalConfig::ClockType::HCLK
			| ClockSignalConfig::ClockType::PCLK1
			| ClockSignalConfig::ClockType::PCLK2;

		clock_init_options._sysclk_source = ClockSignalConfig::SysclkSource::PLLCLK;
		clock_init_options._ahb_clk_divider = ClockSignalConfig::AHBDivider::DIV1;
		clock_init_options._apb1_divider = ClockSignalConfig::APBDivider::DIV2;
		clock_init_options._apb2_divider = ClockSignalConfig::APBDivider::DIV1;
		clock_init_options._flash_latency = ClockSignalConfig::FlashLatency::Latency2;
		ClockSignal::SetConfig(clock_init_options);
	};

	// HAL_Init 函数已经将中断优先级分组设置为 4 了。
	HAL_Init();
	config_clock_source();
	config_clock_signal();
}

void BSP::SystemReset()
{
	Interrupt::SystemReset();
}

bsp::IDelayer &BSP::Delayer()
{
	return Delayer::Instance();
}

bsp::IIndependentWatchDog &BSP::IndependentWatchDog()
{
	return bsp::IndependentWatchDog::Instance();
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
	static std::vector<bsp::IKey *> keys { (size_t)KeyIndex::EnumEndFlag };
	if (!initialized)
	{
		keys[(uint16_t)KeyIndex::Key0] = &Key0::Instance();
		keys[(uint16_t)KeyIndex::Key1] = &Key1::Instance();
	}

	static bsp::KeyScanner key_scanner { keys, Delayer::Instance() };

	// 初始化完成
	initialized = true;
	return key_scanner;
}

bsp::IEventDrivenKey &BSP::WakeUpKey()
{
	return bsp::ExtiWakeUpKey::Instance();
}

bsp::ISerial &BSP::Serial()
{
	return Serial::Instance();
}

bsp::ILcd &BSP::Lcd()
{
	return Lcd::Instance();
}

bsp::IBaseTimer &BSP::BaseTimer()
{
	return BaseTimer1::Instance();
}
