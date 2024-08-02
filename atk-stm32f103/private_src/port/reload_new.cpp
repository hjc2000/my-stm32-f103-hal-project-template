#include "FreeRTOS.h" // Ensure FreeRTOS headers are included
#include "task.h"	  // Required for taskENTER_CRITICAL/taskEXIT_CRITICAL
#include <cstddef>	  // For size_t
#include <new>		  // For std::bad_alloc

/// @brief 利用 heap4 实现。
/// @param size
/// @return
void *operator new(size_t size)
{
	void *ptr = pvPortMalloc(size); // Use FreeRTOS's memory allocation
	if (!ptr)
	{ // If allocation failed, throw bad_alloc
		throw std::bad_alloc();
	}

	return ptr;
}

/// @brief 利用 heap4 实现。
/// @param size
/// @return
void *operator new[](size_t size)
{
	void *ptr = pvPortMalloc(size); // Use FreeRTOS's memory allocation
	if (!ptr)
	{
		// If allocation failed, throw bad_alloc
		throw std::bad_alloc();
	}

	return ptr;
}

/// @brief 利用 heap4 实现。
/// @param ptr
void operator delete(void *ptr) noexcept
{
	vPortFree(ptr); // Use FreeRTOS's memory deallocation
}

/// @brief 利用 heap4 实现。
/// @param ptr
void operator delete[](void *ptr) noexcept
{
	vPortFree(ptr); // Use FreeRTOS's memory deallocation
}

/// @brief 利用 heap4 实现。
/// @param size
/// @param
/// @return
void *operator new(size_t size, const std::nothrow_t &) noexcept
{
	return pvPortMalloc(size);
}

/// @brief 利用 heap4 实现。
/// @param size
/// @param
/// @return
void *operator new[](size_t size, const std::nothrow_t &) noexcept
{
	return pvPortMalloc(size);
}

/// @brief 利用 heap4 实现。
/// @param ptr
/// @param
void operator delete(void *ptr, const std::nothrow_t &) noexcept
{
	vPortFree(ptr);
}

/// @brief 利用 heap4 实现。
/// @param ptr
/// @param
void operator delete[](void *ptr, const std::nothrow_t &) noexcept
{
	vPortFree(ptr);
}

/// @brief 利用 heap4 实现。
/// @param ptr
/// @param
void operator delete(void *ptr, size_t) noexcept
{
	vPortFree(ptr);
}

/// @brief 利用 heap4 实现。
/// @param ptr
/// @param
void operator delete[](void *ptr, size_t) noexcept
{
	vPortFree(ptr);
}
