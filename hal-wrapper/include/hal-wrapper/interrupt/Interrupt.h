#pragma once
#include<hal-wrapper/interrupt/PreemptionPriorityGroup.h>

namespace hal
{
	/// <summary>
	///		静态类。提供中断相关的操作。
	/// </summary>
	class Interrupt
	{
		Interrupt() = delete;

	public:
		/// <summary>
		///		设置抢占优先级组。
		///		- 此函数一次复位后启动只能调用一次，因为抢占优先级组只能设置一次。
		///		  为了防止多次设置，本函数在第二次及以后的调用中会直接返回，什么也不做。
		/// </summary>
		/// <param name="group"></param>
		static void SetPriorityGroup(PreemptionPriorityGroup group)
		{
			static bool have_set = false;
			if (have_set)
			{
				return;
			}

			have_set = true;
			HAL_NVIC_SetPriorityGrouping((uint32_t)group);
		}

		/// <summary>
		///		设置中断优先级。
		/// </summary>
		/// <param name="irq_n">中断号的枚举</param>
		/// <param name="preempt_priority">
		///		中断抢占优先级。范围 [0,15] ，数值越小优先级越高。
		///		- 根据优先级分组，抢占优先级最多可以有 4 位，但此时就没有响应优先级的位置了。
		///		  所以 [0,15] 是理论可以设置的范围，实际有效的范围还得看设置的优先级分组。
		/// </param>
		/// <param name="sub_priority">
		///		中断响应优先级。范围 [0,15] ，数值越小优先级越高。
		///		- 根据优先级分组，响应优先级最多可以有 4 位，但此时就没有抢占优先级的位置了。
		///		  所以 [0,15] 是理论可以设置的范围，实际有效的范围还得看设置的优先级分组。
		/// </param>
		static void SetPriority(IRQn_Type irq_n, uint32_t preempt_priority, uint32_t sub_priority)
		{
			HAL_NVIC_SetPriority(irq_n, preempt_priority, sub_priority);
		}

		/// <summary>
		///		使能中断。
		/// </summary>
		/// <param name="irq_n">中断号</param>
		static void EnableIRQ(IRQn_Type irq_n)
		{
			HAL_NVIC_EnableIRQ(irq_n);
		}

		/// <summary>
		///		禁用中断。
		/// </summary>
		/// <param name="irq_n">中断号</param>
		static void DisableIRQ(IRQn_Type irq_n)
		{
			HAL_NVIC_DisableIRQ(irq_n);
		}

		/// <summary>
		///		执行复位。
		/// </summary>
		static void SystemReset()
		{
			HAL_NVIC_SystemReset();
		}
	};
}