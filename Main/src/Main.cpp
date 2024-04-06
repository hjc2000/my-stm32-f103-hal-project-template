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
	__HAL_RCC_GPIOE_CLK_ENABLE(); /* IO口PE时钟使能 */

	g_gpio_port_b.InitPin(
		GpioPin::Pin5,
		GpioPinMode::Output_PushPull,
		GpioPinPull::PullUp,
		GpioPinSpeed::High
	);

	GPIO_InitTypeDef gpio_init_options;
	gpio_init_options.Pin = GPIO_PIN_8;			  /* LED0引脚 */
	gpio_init_options.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_options.Pull = GPIO_PULLDOWN;
	gpio_init_options.Speed = GPIO_SPEED_FREQ_HIGH;
	//HAL_GPIO_Init(GPIOB, &gpio_init_options);


	gpio_init_options.Pin = GPIO_PIN_5;		/* LED1引脚 */
	HAL_GPIO_Init(GPIOE, &gpio_init_options); /* 初始化LED1引脚 */
}