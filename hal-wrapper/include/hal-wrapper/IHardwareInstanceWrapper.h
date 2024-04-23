#pragma once
#include<hal.h>

namespace hal
{
	/// <summary>
	///		
	/// </summary>
	/// <typeparam name="HardwareTypeDef">
	///		HAL 库中为外设定义的结构体。利用结构体字段地址偏移量自动递增的特性，
	///		使得结构体字段与寄存器一一对应，通过将外设基地址强制转换为结构体指针，
	///		即可通过访问结构体对象字段的方式读写寄存器。
	/// </typeparam>
	template<typename HardwareTypeDef>
	class IHardwareInstanceWrapper
	{
	private:
		IHardwareInstanceWrapper(IHardwareInstanceWrapper const &o) = delete;
		IHardwareInstanceWrapper &operator=(IHardwareInstanceWrapper const &o) = delete;

	protected:
		IHardwareInstanceWrapper() = default;

	public:
		virtual HardwareTypeDef *HardwareInstance() = 0;
	};
}