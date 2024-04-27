#include "FreeRTOS.h"   // Ensure FreeRTOS headers are included
#include "task.h"       // Required for taskENTER_CRITICAL/taskEXIT_CRITICAL
#include <cstddef>      // For size_t
#include <new>          // For std::bad_alloc

void *operator new(size_t size)
{
	void *ptr = pvPortMalloc(size);  // Use FreeRTOS's memory allocation
	if (!ptr)
	{                      // If allocation failed, throw bad_alloc
		throw std::bad_alloc();
	}

	return ptr;
}

void *operator new[](size_t size)
{
	void *ptr = pvPortMalloc(size);  // Use FreeRTOS's memory allocation
	if (!ptr)
	{                      // If allocation failed, throw bad_alloc
		throw std::bad_alloc();
	}

	return ptr;
}

void operator delete(void *ptr) noexcept
{
	vPortFree(ptr);  // Use FreeRTOS's memory deallocation
}

void operator delete[](void *ptr) noexcept
{
	vPortFree(ptr);  // Use FreeRTOS's memory deallocation
}

// Optional: define the nothrow versions of new, which should not throw exceptions
void *operator new(size_t size, const std::nothrow_t &) noexcept
{
	return pvPortMalloc(size);
}

void *operator new[](size_t size, const std::nothrow_t &) noexcept
{
	return pvPortMalloc(size);
}

void operator delete(void *ptr, const std::nothrow_t &) noexcept
{
	vPortFree(ptr);
}

void operator delete[](void *ptr, const std::nothrow_t &) noexcept
{
	vPortFree(ptr);
}

// Optional: define matching delete for exceptions handling in new
void operator delete(void *ptr, size_t) noexcept
{
	vPortFree(ptr);
}

void operator delete[](void *ptr, size_t) noexcept
{
	vPortFree(ptr);
}
