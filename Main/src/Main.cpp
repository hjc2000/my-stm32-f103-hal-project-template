#include"Main.h"
#include"sys.h"
#include"usart.h"
#include<atk-stm32f103/Clock.h>
#include<hal-wrapper/GpioPort.h>
#include<hal-wrapper/Systic.h>

void init_gpio(void);

void Main()
{
	HAL_Init();
	config_72mhz_hclk();
	init_gpio();

	while (1)
	{
		g_gpio_port_b.DigitalWritePin(GpioPin::Pin5, 1);
		g_gpio_port_b.DigitalWritePin(GpioPin::Pin8, 1);
		g_gpio_port_e.DigitalWritePin(GpioPin::Pin5, 0);
		Systic::NopLoopDelay(std::chrono::seconds(1));
		g_gpio_port_b.DigitalWritePin(GpioPin::Pin5, 0);
		g_gpio_port_b.DigitalWritePin(GpioPin::Pin8, 0);
		g_gpio_port_e.DigitalWritePin(GpioPin::Pin5, 1);
		Systic::NopLoopDelay(std::chrono::seconds(1));
	}
}

void init_gpio(void)
{
	g_gpio_port_a.EnableClock();
	g_gpio_port_b.EnableClock();
	g_gpio_port_e.EnableClock();

	GpioPinOptions gpio_pin_options;
	gpio_pin_options._mode = GpioPinMode::Output_PushPull;
	gpio_pin_options._pull_mode = GpioPinPull::PullDown;
	gpio_pin_options._speed = GpioPinSpeed::High;
	g_gpio_port_b.InitPin(GpioPin::Pin5, gpio_pin_options);

	gpio_pin_options._mode = GpioPinMode::Output_PushPull;
	gpio_pin_options._pull_mode = GpioPinPull::PullDown;
	gpio_pin_options._speed = GpioPinSpeed::High;
	//g_gpio_port_b.InitPin(GpioPin::Pin8, gpio_pin_options);

	gpio_pin_options._mode = GpioPinMode::Output_PushPull;
	gpio_pin_options._pull_mode = GpioPinPull::PullDown;
	gpio_pin_options._speed = GpioPinSpeed::High;
	g_gpio_port_e.InitPin(GpioPin::Pin5, gpio_pin_options);
}
