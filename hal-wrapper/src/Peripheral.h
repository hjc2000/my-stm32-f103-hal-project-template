#pragma once
#include<GpioPort.h>

#ifdef GPIOA
extern GpioPort &g_gpio_port_a;
#endif // GPIOA

#ifdef GPIOB
extern GpioPort &g_gpio_port_b;
#endif // GPIOB

#ifdef GPIOE
extern GpioPort &g_gpio_port_e;
#endif // GPIOE
