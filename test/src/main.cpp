#include<atk-stm32f103/AtkClock.h>
#include<atk-stm32f103/AtkExtiKey.h>
#include<atk-stm32f103/AtkKey.h>
#include<atk-stm32f103/dependencies-provider.h>
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

void TestKeyScanner();
void TestUart1();
void TestIndependentWatchDog();
void TestWindowWatchDog();

int main(void)
{
	TestKeyScanner();
	//TestExtiKey();
	//TestUart1();
	//TestIndependentWatchDog();
	//TestWindowWatchDog();
}

void TestKeyScanner()
{
	HAL_Init();
	config_72mhz_hclk();

	while (1)
	{
		DP_KeyScanner().ScanKeys();
		if (DP_KeyScanner().HasKeyDownEvent(0))
		{
			DP_RedDigitalLed().Toggle();
		}

		if (DP_KeyScanner().HasKeyDownEvent(1))
		{
			DP_GreenDigitalLed().Toggle();
		}

		if (DP_KeyScanner().HasKeyDownEvent(2))
		{
			DP_GreenDigitalLed().Toggle();
		}
	}
}

void TestUart1()
{
	HAL_Init();
	config_72mhz_hclk();
	DP_RedDigitalLed().TurnOn();
	Uart1::Instance().Initialize();
	Uart1::Instance()._on_receive_completed_interrupt = []()
	{
		DP_RedDigitalLed().Toggle();
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
	DP_RedDigitalLed().TurnOn();
	IndependentWatchDog::Instance().SetWatchDogTimeoutDuration(std::chrono::milliseconds(1000));

	while (1)
	{
		DP_KeyScanner().ScanKeys();
		if (DP_KeyScanner().HasKeyDownEvent(0))
		{
			IndependentWatchDog::Instance().Feed();
		}

		if (DP_KeyScanner().HasKeyDownEvent(1))
		{
			IndependentWatchDog::Instance().Feed();
		}

		if (DP_KeyScanner().HasKeyDownEvent(2))
		{
			IndependentWatchDog::Instance().Feed();
		}
	}
}

void TestWindowWatchDog()
{
	HAL_Init();
	config_72mhz_hclk();
	DP_RedDigitalLed().TurnOn();
	Delayer::Instance().Delay(std::chrono::milliseconds(1000));

	WindowWatchDogInitOptions options;
	options._counter_reload_value = 0x7f;
	options._window_upper_bound = 0x5f;
	options._prescaler = WindowWatchDogPrescaler::Div8;
	options._early_wakeup_interrupt_mode = WindowWatchDogEarlyWakeupInterruptMode::Enable;
	WindowWatchDog::Instance().Initialize(options);
	WindowWatchDog::Instance()._on_early_wakeup_interrupt = []()
	{
		DP_GreenDigitalLed().Toggle();
	};

	while (true)
	{
		DP_RedDigitalLed().TurnOff();
	}
}
