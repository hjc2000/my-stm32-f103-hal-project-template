#include"BinarySemaphore.h"

using namespace atk;

BinarySemaphore::BinarySemaphore()
{
	handle = xSemaphoreCreateBinary();
	if (handle == nullptr)
	{
		throw std::runtime_error{ "创建信号量失败" };
	}
}

BinarySemaphore::~BinarySemaphore()
{
	vSemaphoreDelete(handle);
}

void BinarySemaphore::Release()
{
	xSemaphoreGive(handle);
}

void BinarySemaphore::ReleaseFromISR()
{
	xSemaphoreGiveFromISR(handle, &_higher_priority_task_woken);
}

void BinarySemaphore::Acquire()
{
	xSemaphoreTake(handle, portMAX_DELAY);
}

bool BinarySemaphore::TryAcquire(TickType_t ticks)
{
	return xSemaphoreTake(handle, ticks) == pdTRUE;
}
