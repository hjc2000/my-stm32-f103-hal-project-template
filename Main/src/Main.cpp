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
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);		/* PB5置1 */
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);		/* PB5置1 */
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_RESET);	/* PE5置0 */
		g_systic_operator.NopLoopDelay(std::chrono::seconds(1));
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);	/* PB5置0 */
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);	/* PB5置0 */
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);		/* PE5置1 */
		g_systic_operator.NopLoopDelay(std::chrono::seconds(1));
	}
}

void led_init(void)
{
	g_gpio_port_a.EnableClock();
	g_gpio_port_b.EnableClock();
	g_gpio_port_e.EnableClock();

	GpioPinOptions options;
	options.mode = GpioPinMode::Output_PushPull;
	options.pull_mode = GpioPinPull::PullDown;
	options.speed = GpioPinSpeed::High;
	g_gpio_port_b.InitPin(GpioPin::Pin5, options);

	options.mode = GpioPinMode::Output_PushPull;
	options.pull_mode = GpioPinPull::PullDown;
	options.speed = GpioPinSpeed::High;
	g_gpio_port_b.InitPin(GpioPin::Pin8, options);

	options.mode = GpioPinMode::Output_PushPull;
	options.pull_mode = GpioPinPull::PullDown;
	options.speed = GpioPinSpeed::High;
	g_gpio_port_e.InitPin(GpioPin::Pin5, options);
}