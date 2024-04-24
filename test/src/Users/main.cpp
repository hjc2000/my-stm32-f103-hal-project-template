#include<atk-stm32f103/AtkClock.h>
#include<atk-stm32f103/AtkExtiKey.h>
#include<atk-stm32f103/AtkKey.h>
#include<atk-stm32f103/AtkKeyScanner.h>
#include<atk-stm32f103/AtkLed.h>
#include<hal-wrapper/clock/Delayer.h>
#include<hal-wrapper/clock/Systic.h>
#include<hal-wrapper/peripheral/gpio/GpioPort.h>
#include<hal-wrapper/peripheral/independent-watch-dog/IndependentWatchDog.h>
#include<hal-wrapper/peripheral/uart/Uart1.h>
#include<hal-wrapper/peripheral/window-watch-dog/WindowWatchDog.h>
#include<string>

using namespace hal;
using namespace atk;
using namespace bsp;

void TestUart1();
void TestIndependentWatchDog();
void TestWindowWatchDog();

int main(void)
{
	//TestKeyScanner();
	//TestExtiKey();
	//TestUart1();
	//TestIndependentWatchDog();
	TestWindowWatchDog();
}

void TestUart1()
{
	HAL_Init();
	config_72mhz_hclk();
	RedDigitalLed::Instance().TurnOn();
	Uart1::Instance().Initialize();
	Uart1::Instance()._on_receive_completed = []()
	{
		RedDigitalLed::Instance().Toggle();
	};

	std::string str = "hello world\n";
	while (1)
	{
		Delayer::Instance().Delay(std::chrono::seconds(1));
		Uart1::Instance().SendWithDma((uint8_t const *)(str.c_str()), str.length());
		Uart1::Instance().WaitForDmaTx();
		Uart1::Instance().PerepareForNextDmaTx();
	}
}

void TestIndependentWatchDog()
{
	HAL_Init();
	config_72mhz_hclk();
	Delayer::Instance().Delay(std::chrono::milliseconds(500));
	RedDigitalLed::Instance().TurnOn();
	IndependentWatchDog::Instance().SetWatchDogTimeoutDuration(std::chrono::milliseconds(1000));

	while (1)
	{
		AtkKeyScanner::Instance().ScanKeys();
		auto key_down_events = AtkKeyScanner::Instance().GetKeyDownEvents();

		if (key_down_events[0])
		{
			IndependentWatchDog::Instance().Feed();
		}

		if (key_down_events[1])
		{
			IndependentWatchDog::Instance().Feed();
		}

		if (key_down_events[2])
		{
			IndependentWatchDog::Instance().Feed();
		}
	}
}

void TestWindowWatchDog()
{
	HAL_Init();
	config_72mhz_hclk();
	RedDigitalLed::Instance().TurnOn();
	Delayer::Instance().Delay(std::chrono::milliseconds(1000));

	WindowWatchDogInitOptions options;
	options._counter_reload_value = 0x7f;
	options._window_upper_bound = 0x5f;
	options._prescaler = WindowWatchDogPrescaler::Div8;
	options._early_wakeup_interrupt_mode = WindowWatchDogEarlyWakeupInterruptMode::Enable;
	WindowWatchDog::Instance().Initialize(options);
	WindowWatchDog::Instance()._on_early_wakeup_interrupt = []()
	{
		GreenDigitalLed::Instance().Toggle();
	};

	while (true)
	{
		RedDigitalLed::Instance().TurnOff();
	}
}
