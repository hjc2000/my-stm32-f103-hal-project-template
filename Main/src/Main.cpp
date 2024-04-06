#include"Main.h"
#include"sys.h"
#include"usart.h"
#include<Peripheral.h>
#include<SysticOperator.h>

void led_init(void);

void Main()
{
	HAL_Init();									/* 初始化HAL库 */
	sys_stm32_clock_init(RCC_PLL_MUL9);		/* 设置时钟, 72Mhz */
	led_init();									/* LED初始化 */

	while (1)
	{
		g_gpio_port_b.DigitalWritePin(GpioPin::Pin5, 1);
		g_gpio_port_b.DigitalWritePin(GpioPin::Pin8, 1);
		g_gpio_port_e.DigitalWritePin(GpioPin::Pin5, 0);
		g_systic_operator.NopLoopDelay(std::chrono::seconds(1));
		g_gpio_port_b.DigitalWritePin(GpioPin::Pin5, 0);
		g_gpio_port_b.DigitalWritePin(GpioPin::Pin8, 0);
		g_gpio_port_e.DigitalWritePin(GpioPin::Pin5, 1);
		g_systic_operator.NopLoopDelay(std::chrono::seconds(1));
	}
}

void led_init(void)
{
	g_gpio_port_a.EnableClock();
	g_gpio_port_b.EnableClock();
	g_gpio_port_e.EnableClock();

	GpioPinOptions gpio_pin_options;
	gpio_pin_options.mode = GpioPinMode::Output_PushPull;
	gpio_pin_options.pull_mode = GpioPinPull::PullDown;
	gpio_pin_options.speed = GpioPinSpeed::High;
	g_gpio_port_b.InitPin(GpioPin::Pin5, gpio_pin_options);

	gpio_pin_options.mode = GpioPinMode::Output_PushPull;
	gpio_pin_options.pull_mode = GpioPinPull::PullDown;
	gpio_pin_options.speed = GpioPinSpeed::High;
	//g_gpio_port_b.InitPin(GpioPin::Pin8, gpio_pin_options);

	gpio_pin_options.mode = GpioPinMode::Output_PushPull;
	gpio_pin_options.pull_mode = GpioPinPull::PullDown;
	gpio_pin_options.speed = GpioPinSpeed::High;
	g_gpio_port_e.InitPin(GpioPin::Pin5, gpio_pin_options);
}
