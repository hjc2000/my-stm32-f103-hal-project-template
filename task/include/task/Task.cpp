#include"Task.h"

task::Task task::Task::Run(std::function<void()> func)
{
	task::Task *task = new task::Task{};
	task->_func = func;
	auto f = [](void *param)
	{
		task::Task *task = (task::Task *)param;
		task->_func();
		delete task;
	};

	// usStackDepth 参数的单位不是字节，而是字。32 位 CPU 一个字是 4 字节。
	xTaskCreate(
		f,
		"task::Task",
		128,
		task,
		1,
		&task->_handle
	);

	// 本类对象内的字段借由拷贝构造函数拷贝给接收返回值的对象
	return *task;
}
