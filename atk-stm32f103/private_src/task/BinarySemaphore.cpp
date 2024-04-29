#include"BinarySemaphore.h"

using namespace bsp;

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

void bsp::BinarySemaphore::Release()
{
	xSemaphoreGive(handle);
}

void bsp::BinarySemaphore::ReleaseFromISR()
{
	xSemaphoreGiveFromISR(handle, &_higher_priority_task_woken);
}

void bsp::BinarySemaphore::Acquire()
{
	xSemaphoreTake(handle, portMAX_DELAY);
}

bool bsp::BinarySemaphore::TryAcquire(TickType_t ticks)
{
	return xSemaphoreTake(handle, ticks) == pdTRUE;
}
