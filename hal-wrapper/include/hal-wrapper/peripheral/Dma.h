#pragma once
#include<hal-wrapper/IHandleWrapper.h>
#include<hal-wrapper/peripheral/DmaEnum.h>
#include<hal-wrapper/peripheral/IPeripheral.h>

namespace hal
{
	#pragma region DmaInitOptions
	/// <summary>
	///		DMA 初始化选项。
	/// </summary>
	class DmaInitOptions
	{
	public:
		DmaInitOptions() = default;
		DmaInitOptions(DmaInitOptions const &o) = default;
		DmaInitOptions(DMA_InitTypeDef const &o);
		DmaInitOptions &operator=(DmaInitOptions const &o) = default;
		DmaInitOptions &operator=(DMA_InitTypeDef const &o);

		/// <summary>
		///		数据传输方向
		/// </summary>
		DmaDataTransferDirection _direction;

		/// <summary>
		///		一次传输结束后，外设地址是否应该递增。
		/// </summary>
		DmaPeripheralIncMode _peripheral_inc_mode;

		/// <summary>
		///		一次传输结束后，内存地址是否应该递增。
		/// </summary>
		DmaMemoryIncMode _mem_inc_mode;

		/// <summary>
		///		外设中的数据的对齐方式。
		/// </summary>
		PeripheralDataAlignment _peripheral_data_alignment;

		/// <summary>
		///		内存中的数据的对齐方式。
		/// </summary>
		MemoryDataAlignment _mem_data_alignment;

		/// <summary>
		///		数据传输模式。
		///		- 可以选择普通模式或循环模式。循环模式不能用于内存到内存传输模式。
		/// </summary>
		DmaMode _mode;

		/// <summary>
		///		此通道的传输优先级。
		/// </summary>
		DmaPriority _priority;

		operator DMA_InitTypeDef() const;
	};
	#pragma endregion

	template<typename HandleType>
	class IDmaLinkable
	{
	public:
		virtual HandleType *Handle() = 0;
		virtual DMA_HandleTypeDef *HDmaTx() = 0;
		virtual DMA_HandleTypeDef *HDmaRx() = 0;
	};

	/// <summary>
	///		DMA 抽象类
	/// </summary>
	class Dma :
		public IPeripheral,
		public IHandleWrapper<DMA_HandleTypeDef>
	{
		DMA_HandleTypeDef _handle;

	public:
		void Initialize(DmaInitOptions const &options)
		{
			_handle.Init = options;
			HAL_DMA_Init(&_handle);
		}

		/// <summary>
		///		本对象内部的 DMA_HandleTypeDef 句柄对象的指针。
		/// </summary>
		/// <returns></returns>
		DMA_HandleTypeDef *Handle() override
		{
			return &_handle;
		}

		void SetParent(DMA_HandleTypeDef *&parent)
		{

		}
	};
}