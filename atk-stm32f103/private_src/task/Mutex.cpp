#include"Mutex.h"

task::Mutex::Mutex()
{
	_freertos_mutex = xSemaphoreCreateMutex();
	if (_freertos_mutex == NULL)
	{
		throw std::runtime_error{ "Mutex 构造失败" };
	}
}

task::Mutex::~Mutex()
{
	if (_freertos_mutex != NULL)
	{
		vSemaphoreDelete(_freertos_mutex);
	}
}
