#include"Main.h"
#include<atk-stm32f103/Clock.h>
#include<atk-stm32f103/ExtiKey.h>
#include<atk-stm32f103/Key.h>
#include<atk-stm32f103/Led.h>
#include<hal-wrapper/clock/Delayer.h>
#include<hal-wrapper/clock/Systic.h>
#include<hal-wrapper/peripheral/gpio/GpioPort.h>
#include<hal-wrapper/peripheral/uart/Uart1.h>

using namespace hal;
using namespace atk;

void TestKeyScanner()
{
	HAL_Init();
	config_72mhz_hclk();
	IKey *keys[] = {
		&Key0::Instance(),
		&Key1::Instance(),
		&KeyWakeUp::Instance(),
	};
	KeyScanner<sizeof(keys) / sizeof(IKey *)> key_scanner{ keys };

	while (1)
	{
		key_scanner.ScanKeys();
		auto key_down_events = key_scanner.GetKeyDownEvents();

		if (key_down_events[0])
		{
			RedDigitalLed::Instance().Toggle();
		}

		if (key_down_events[1])
		{
			GreenDigitalLed::Instance().Toggle();
		}

		if (key_down_events[2])
		{
			GreenDigitalLed::Instance().Toggle();
		}
	}
}

void TestInterrupt()
{
	HAL_Init();
	config_72mhz_hclk();
	RedDigitalLed::Instance().TurnOn();
	while (1)
	{
		if (ExtiKey0::Instance().IsPressed())
		{
			RedDigitalLed::Instance().Toggle();
			GreenDigitalLed::Instance().Toggle();
			ExtiKey0::Instance().ClearPressedFlag();
		}
	}
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

	uint8_t buffer[]{ 72,72,72,72 };
	uint16_t buffer_size = sizeof(buffer);
	while (1)
	{
		Delayer::Instance().Delay(std::chrono::seconds(1));
		Uart1::Instance().SendWithDma(buffer, buffer_size);
		Uart1::Instance().WaitForDmaTx();
		Uart1::Instance().PerepareForNextDmaTx();
	}
}
