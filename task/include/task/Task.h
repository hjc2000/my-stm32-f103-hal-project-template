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

		static Task Run(std::function<void()> func);
	};
}
