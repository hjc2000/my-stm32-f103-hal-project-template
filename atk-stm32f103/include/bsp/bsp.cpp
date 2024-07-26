#include "bsp.h"
#include <AtkKey.h>
#include <DigitalLed.h>
#include <ExtiWakeUpKey.h>
#include <FreeRTOS.h>
#include <Lcd.h>
#include <atomic>
#include <base/RentedPtrFactory.h>
#include <bsp-interface/key/KeyScanner.h>
#include <functional>
#include <hal-wrapper/clock/ClockSignal.h>
#include <hal-wrapper/clock/ConfigClockSignal.h>
#include <hal-wrapper/clock/Delayer.h>
#include <hal-wrapper/clock/Osc.h>
#include <hal-wrapper/clock/SysTickClock.h>
#include <hal-wrapper/clock/clock-signal-config/ClockSignalConfig.h>
#include <hal-wrapper/peripheral/base-timer/BaseTimer1.h>
#include <hal-wrapper/peripheral/independent-watch-dog/IndependentWatchDog.h>
#include <hal-wrapper/peripheral/serial/Serial.h>
#include <hal-wrapper/peripheral/window-watch-dog/WindowWatchDog.h>
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

	bsp::Console::Instance().SetOutStream(base::RentedPtrFactory::Create(&BSP::Serial()));
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
	return IndependentWatchDog::Instance();
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
	class KeyScannerInitializer
	{
	private:
		KeyScannerInitializer()
		{
			_keys[(uint16_t)KeyIndex::Key0] = &Key0::Instance();
			_keys[(uint16_t)KeyIndex::Key1] = &Key1::Instance();
			_key_scanner = std::shared_ptr<bsp::KeyScanner>{new bsp::KeyScanner{
				_keys,
			}};
		}

		KeyScannerInitializer(KeyScannerInitializer const &o) = delete;
		KeyScannerInitializer(KeyScannerInitializer &&o) = delete;
		KeyScannerInitializer &operator=(KeyScannerInitializer const &o) = delete;
		KeyScannerInitializer &operator=(KeyScannerInitializer &&o) = delete;

		std::vector<bsp::IKey *> _keys{(size_t)KeyIndex::EnumEndFlag};
		std::shared_ptr<bsp::KeyScanner> _key_scanner;

	public:
		static KeyScannerInitializer &Instance()
		{
			static KeyScannerInitializer o;
			return o;
		}

		IKeyScanner &Scanner()
		{
			return *_key_scanner;
		}
	};

	return KeyScannerInitializer::Instance().Scanner();
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

bsp::Console &BSP::Console()
{
	return bsp::Console::Instance();
}

void TestWindowWatchDog()
{
	BSP::Delayer().Delay(std::chrono::seconds{1});
	BSP::RedDigitalLed().TurnOn();

	hal::WindowWatchDogConfig config;
	config.SetCounterReloadValue(0x7f);
	config.SetWindow(0x5f);
	config.SetPrescaler(hal::WindowWatchDogConfig::PrescalerOption::DIV2);
	config.SetEarlyWakeupInterrupt(hal::WindowWatchDogConfig::EarlyWakeupInterruptOption::Enable);

	hal::WindowWatchDog::Instance().SetEarlyWakeupInterruptCallback([&]()
																	{ BSP::GreenDigitalLed().Toggle(); });

	hal::WindowWatchDog::Instance().Initialize(config);

	while (true)
	{
		BSP::RedDigitalLed().Toggle();
		BSP::Delayer().Delay(std::chrono::seconds{1});
	}
}
