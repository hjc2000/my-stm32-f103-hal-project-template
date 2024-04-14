#pragma once
#include<hal.h>

namespace hal
{
	/// <summary>
	///		抢占优先级组
	/// </summary>
	enum class PreemptionPriorityGroup
	{
		/// <summary>
		///		0 位抢占优先级，4 位响应优先级。
		/// </summary>
		Group0 = NVIC_PRIORITYGROUP_0,

		/// <summary>
		///		1 位抢占优先级，3 位响应优先级。
		/// </summary>
		Group1 = NVIC_PRIORITYGROUP_1,

		/// <summary>
		///		2 位抢占优先级，2 位响应优先级。
		/// </summary>
		Group2 = NVIC_PRIORITYGROUP_2,

		/// <summary>
		///		3 位抢占优先级，1 位响应优先级。
		/// </summary>
		Group3 = NVIC_PRIORITYGROUP_3,

		/// <summary>
		///		4 位抢占优先级，0 位响应优先级。
		/// </summary>
		Group4 = NVIC_PRIORITYGROUP_4,
	};
}