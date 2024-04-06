#include"Main.h"
#include"sys.h"
#include"usart.h"
#include<Clock.h>
#include<Peripheral.h>

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
		systick_nop_loop_delay_ms(1000);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);	/* PB5置0 */
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);	/* PB5置0 */
		HAL_GPIO_WritePin(GPIOE, GPIO_PIN_5, GPIO_PIN_SET);		/* PE5置1 */
		systick_nop_loop_delay_ms(1000);
	}
}

void led_init(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE(); /* IO口PB时钟使能 */
	__HAL_RCC_GPIOE_CLK_ENABLE(); /* IO口PE时钟使能 */

	GPIO_InitTypeDef gpio_init_options;
	gpio_init_options.Pin = GPIO_PIN_5;			  /* LED0引脚 */
	gpio_init_options.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_options.Pull = GPIO_PULLUP;
	gpio_init_options.Speed = GPIO_SPEED_FREQ_HIGH; /* 高速 */
	HAL_GPIO_Init(GPIOB, &gpio_init_options);		  /* 初始化LED0引脚 */

	gpio_init_options.Pin = GPIO_PIN_8;			  /* LED0引脚 */
	gpio_init_options.Mode = GPIO_MODE_OUTPUT_PP;
	gpio_init_options.Pull = GPIO_PULLDOWN;
	gpio_init_options.Speed = GPIO_SPEED_FREQ_HIGH;
	//HAL_GPIO_Init(GPIOB, &gpio_init_options);


	gpio_init_options.Pin = GPIO_PIN_5;		/* LED1引脚 */
	HAL_GPIO_Init(GPIOE, &gpio_init_options); /* 初始化LED1引脚 */
}