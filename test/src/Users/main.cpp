#include<atk-stm32f103/AtkKeyScanner.h>
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
using namespace bsp;

void TestUart1();

int main(void)
{
	TestKeyScanner();
	//TestExtiKey();
	//TestUart1();
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
