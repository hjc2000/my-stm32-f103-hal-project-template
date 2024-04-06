#pragma once
// 这个头文件要最先包含，所以放到双引号里，避免 vs 的头文件排序把它放到后面去
#include"stm32f1xx_hal.h"
#include<stdint.h>
#include<stm32f1xx_hal_def.h>

#ifdef __cplusplus
extern "C" {
	#endif

	typedef enum
	{
		Peripheral_GPIO_A,
		Peripheral_GPIO_B,
		Peripheral_GPIO_C,
		Peripheral_GPIO_D,
	} Peripheral;



	/// <summary>
	///		检查指定的外设时钟是否使能
	/// </summary>
	/// <param name="p"></param>
	/// <returns></returns>
	uint8_t peripheral_clock_enabled(Peripheral p);



	#ifdef __cplusplus
}
#endif // _cplusplus
