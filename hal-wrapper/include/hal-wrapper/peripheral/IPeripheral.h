#pragma once
#include<hal.h>

namespace hal
{
	/// <summary>
	///		外设接口
	/// </summary>
	/// <typeparam name="HardwareTypeDef">
	///		HAL 库中为外设定义的结构体。利用结构体字段地址偏移量自动递增的特性，
	///		使得结构体字段与寄存器一一对应，通过将外设基地址强制转换为结构体指针，
	///		即可通过访问结构体对象字段的方式读写寄存器。
	/// </typeparam>
	template<typename HardwareTypeDef>
	class IPeripheral
	{
	private:
		IPeripheral(IPeripheral const &o) = delete;
		IPeripheral &operator=(IPeripheral const &o) = delete;

	protected:
		IPeripheral() = default;

	public:
		virtual HardwareTypeDef *HardwareInstance() = 0;

		virtual bool IsClockEnabled() = 0;

		bool IsClockDisabled()
		{
			return !IsClockEnabled();
		}

		/// <summary>
		///		使能时钟。
		///		派生类实现时需要注意，在执行使能的操作前要先判断是否已经使能了。
		/// </summary>
		virtual void EnableClock() = 0;

		/// <summary>
		///		失能时钟。
		///		派生类实现时需要注意，在执行失能的操作前要先判断是否已经失能了。
		/// </summary>
		virtual void DisableClock() = 0;
	};
}