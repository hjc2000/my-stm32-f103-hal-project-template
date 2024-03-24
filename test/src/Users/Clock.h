#pragma once
#include"stm32f1xx_hal.h"
#include<core_cm3.h>
#include<stdint.h>
#include<stm32f103xe.h>
#include<stm32f1xx_hal_rcc.h>

/// <summary>
///		获取 SysTick 寄存器组中的 CTRL 寄存器的 COUNTFLAG 位的值。
///		该位是只读的。
/// </summary>
/// 
/// <note>
///		SysTick 是一个减计数的计数器。如果自上次读取 SysTick 的值后，SysTick 减计数到 0 了，
///		说明计数值要发生回绕了，此时 CTRL 寄存器的 COUNTFLAG 位会置位，则本函数返回 1.
/// </note>
/// <note>
///		读取 COUNTFLAG 位会导致 COUNTFLAG 位自动清零。
/// </note>
/// 
/// <returns>发生了回绕 返回非 0 值，没有发生回绕返回 0.</returns>
uint8_t systick_ctrl_count_flag();

/// <summary>
///		CLKSOURCE 位为 0 表示使用 HCLK / 8 作为时钟源。
///		CLKSOURCE 位为 1 表示使用 HCLK 直接作为时钟源。
///		CLKSOURCE 位是可读可写的。
/// </summary>
/// <returns></returns>
uint8_t systick_ctrl_clock_source();
uint8_t systick_ctrl_clock_source_is_hclk();
uint8_t systick_ctrl_clock_source_is_hclk_div8();

/// <summary>
///		选择 SysTick 的时钟源。
/// </summary>
/// <param name="div8">
///		为 true 表示将 HCLK 8 分频后输入 SysTick。
///		为 false 表示直接将 HCLK 输入 SysTick，不经过分频。
/// </param>
void set_systick_ctrl_clock_source(uint8_t div8);

/// <summary>
///		获取 Systick 的时钟源的频率
/// </summary>
/// <returns></returns>
uint32_t systick_clock_source_freq();

/// <summary>
///		获取 SysTick 的 LOAD 寄存器的 RELOAD 部分的值。
///		RELOAD 占据 LOAD 寄存器的低 23 位。
///		
///		RELOAD 是用来在计数值递减到 0 后，下一个时钟周期装载到计数器中的。
/// </summary>
/// <returns></returns>
uint32_t systick_load_reload();

/// <summary>
///		获取 SysTick 的 VAL 寄存器的 CURRENT 部分的值。
///		CURRENT 部分占据了寄存器的低 23 位，表示当前计数值。
/// </summary>
/// <note>
///		CURRENT 可读可写。只不过这里的写并不是如你所愿地将数据赋予 CURRENT。
///		写入 CURRENT 会导致 CURRENT 清零，同时会导致 CTRL 寄存器的
///		COUNTFLAG 位清零。
/// </note>
/// <returns>当前计数值</returns>
uint32_t systick_val_current();

#pragma region 利用SysTick进行延时
/// <summary>
///		通过空指令循环来延时
/// </summary>
/// <param name="tick_count">要延时的 SysTick 计数值</param>
void systick_nop_loop_delay_tick(uint32_t tick_count);

/// <summary>
///		通过空指令循环来延时
/// </summary>
/// <param name="us_count">要延时多少微秒</param>
void systick_nop_loop_delay_us(uint32_t us_count);

void systick_nop_loop_delay_ms(uint32_t ms_count);
#pragma endregion
