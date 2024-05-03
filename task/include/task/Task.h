#pragma once
#include<FreeRTOS.h>
#include<functional>
#include<memory>
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
		/// <summary>
		///		创建一个任务以执行 func。
		///		* 任务的栈大小使用默认值 DefaultStackDepth()
		/// </summary>
		/// <param name="func"></param>
		/// <param name="stack_depth"></param>
		/// <returns></returns>
		static std::shared_ptr<task::Task> Run(std::function<void()> func, uint16_t stack_depth);
	};
}
