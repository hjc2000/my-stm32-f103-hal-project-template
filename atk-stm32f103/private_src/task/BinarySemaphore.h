#pragma once
#include"FreeRTOS.h"
#include"semphr.h"
#include<stdexcept>

namespace bsp
{
	/// <summary>
	///		包装 freertos 的二进制信号量。
	/// </summary>
	class BinarySemaphore
	{
	private:
		SemaphoreHandle_t handle;

	public:
		BinarySemaphore();
		~BinarySemaphore();

		void Release();
		void Acquire();
		bool TryAcquire(TickType_t ticks = 0);
		void ReleaseFromISR(BaseType_t *higherPriorityTaskWoken);
	};
}
