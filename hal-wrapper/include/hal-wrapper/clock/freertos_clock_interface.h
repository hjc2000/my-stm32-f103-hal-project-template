#pragma once
#include<stdint.h>

/* libfreertos 需要这些符号。
* 因为 libfreertos 链接到本库，而这里的函数是本库提供的，所以 libfreertos 无法使用本库
* 的头文件来获取这些符号，libfreertos 需要声明，然后定义由本库实现。
*
* 这是一种链接时解决依赖的技巧，可以反向传递依赖。
* 即：
*
*	A：定义符号
*	B：#include<A的头文件>，其实导入头文件也就是导入符号的声明。
*	A -----链接到----> B
*	A -----提供符号给-----> B
*
*	A：声明符号（A 无法包含 B 的头文件，但是可以手动复制函数签名，从而进行声明）
*	B：定义符号
*	A -----链接到----> B
*	B -----提供符号给-----> A
*/
extern "C"
{
	/// <summary>
	///		供 freertos 获取 CPU 频率。
	/// </summary>
	/// <returns></returns>
	uint32_t freertos_get_cpu_freq();

	/// <summary>
	///		供 freertos 获取硬件 systic 时钟频率。
	/// </summary>
	/// <returns></returns>
	uint32_t freertos_get_systic_clock_freq();
}
