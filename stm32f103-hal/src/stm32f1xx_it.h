#pragma once
#include<functional>

extern std::function<void()> _on_nmi;
extern std::function<void()> _on_hard_fault;
extern std::function<void()> _on_memory_nanage;
extern std::function<void()> _on_bus_fault;
extern std::function<void()> _on_usage_fault;
extern std::function<void()> _on_svc;
extern std::function<void()> _on_debug_mon;
extern std::function<void()> _on_pend_sv;
extern std::function<void()> _on_systic;

/* 中断向量函数的定义。
*
* 本来 stm32 的设计是：
*	启动汇编文件中定义了中断向量表，中断向量表中引用了中断处理函数。同时，启动文件里面定义了
*	weak 版本的中断处理函数。
*
* 这样有个问题，如果强符号是定义在静态库中的，链接时，链接器直接使用 weak 版本，而不会去搜索
* 静态库中的强符号版本。
*
* 所以，最终决定，从启动文件中删除 weak 版本的定义，在这里定义强符号版本，然后对外提供回调。
*/

extern "C"
{
	void NMI_Handler();
	void HardFault_Handler();
	void MemManage_Handler();
	void BusFault_Handler();
	void UsageFault_Handler();
	void SVC_Handler();
	void DebugMon_Handler();
	void PendSV_Handler();
	void SysTick_Handler();
}
