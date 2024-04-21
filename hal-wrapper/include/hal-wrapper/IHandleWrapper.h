#pragma once

namespace hal
{
	/// <summary>
	///		如果一个类内部含有名称类似于 DMA_HandleTypeDef 这种 XXX_HandleTypeDef
	///		的 HAL 库句柄对象，则继承本接口。
	/// 
	///		但是，必须是自己包装的句柄才能够继承本接口并将句柄的指针返回。例如，只有 DMA
	///		的包装类才能继承 IHandleWrapper<DMA_HandleTypeDef> 类，其他类，例如串口类，
	///		虽然也有 DMA_HandleTypeDef* 的字段，但是它并不能继承
	///		IHandleWrapper<DMA_HandleTypeDef> 类。
	/// </summary>
	/// <typeparam name="HandleType"></typeparam>
	template<typename HandleType>
	class IHandleWrapper
	{
	public:
		/// <summary>
		///		返回 XXX_HandleTypeDef 的指针。
		/// </summary>
		/// <returns></returns>
		virtual HandleType *Handle() = 0;
	};
}