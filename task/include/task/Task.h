#pragma once
#include<FreeRTOS.h>
#include<functional>
#include<stdint.h>
#include<task.h>

namespace task
{
	class Task
	{
	private:
		std::function<void()> _func;
		TaskHandle_t _handle;

	public:
		TaskHandle_t Handle()
		{
			return _handle;
		}

		/// <summary>
		///		任务的栈大小的默认值。
		///		* 返回的是引用，可以修改。
		/// </summary>
		/// <returns></returns>
		static uint16_t &DefaultStackDepth()
		{
			static uint16_t default_stack_depth = 128;
			return default_stack_depth;
		}

		/// <summary>
		///		创建一个任务以执行 func。
		///		* 任务的栈大小使用默认值 DefaultStackDepth()
		/// </summary>
		/// <param name="func"></param>
		/// <returns></returns>
		static Task Run(std::function<void()> func);
	};
}
