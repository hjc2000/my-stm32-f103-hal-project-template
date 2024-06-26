#pragma once
#include<hal.h>

namespace hal
{
	/// <summary>
	///		DMA 初始化选项。
	/// </summary>
	class DmaConfig
	{
	public:
		DmaConfig() = default;
		DmaConfig(DmaConfig const &o) = default;
		DmaConfig(DMA_InitTypeDef const &o);
		DmaConfig &operator=(DmaConfig const &o) = default;
		DmaConfig &operator=(DMA_InitTypeDef const &o);
		operator DMA_InitTypeDef() const;

		enum class DataTransferDirection
		{
			PeripheralToMemory = DMA_PERIPH_TO_MEMORY,
			MemoryToPeripheral = DMA_MEMORY_TO_PERIPH,
			MomoryToMemory = DMA_MEMORY_TO_MEMORY,
		};

		/// <summary>
		///		数据传输方向
		/// </summary>
		DataTransferDirection _data_transfer_direction;

		enum class PeripheralIncMode
		{
			Enable = DMA_PINC_ENABLE,
			Disable = DMA_PINC_DISABLE,
		};

		/// <summary>
		///		一次传输结束后，外设地址是否应该递增。
		/// </summary>
		PeripheralIncMode _peripheral_inc_mode;

		enum class MemoryIncMode
		{
			Enable = DMA_MINC_ENABLE,
			Disable = DMA_MINC_DISABLE,
		};

		/// <summary>
		///		一次传输结束后，内存地址是否应该递增。
		/// </summary>
		MemoryIncMode _mem_inc_mode;

		enum class PeripheralDataAlignment
		{
			Byte = DMA_PDATAALIGN_BYTE,

			/// <summary>
			///		16 位
			/// </summary>
			HalfWord = DMA_PDATAALIGN_HALFWORD,

			/// <summary>
			///		32 位
			/// </summary>
			Word = DMA_PDATAALIGN_WORD,
		};

		/// <summary>
		///		外设中的数据的对齐方式。
		/// </summary>
		PeripheralDataAlignment _peripheral_data_alignment;

		enum class MemoryDataAlignment
		{
			Byte = DMA_MDATAALIGN_BYTE,

			/// <summary>
			///		16 位
			/// </summary>
			HalfWord = DMA_MDATAALIGN_HALFWORD,

			/// <summary>
			///		32 位
			/// </summary>
			Word = DMA_MDATAALIGN_WORD,
		};

		/// <summary>
		///		内存中的数据的对齐方式。
		/// </summary>
		MemoryDataAlignment _mem_data_alignment;

		enum class Mode
		{
			Normal = DMA_NORMAL,
			Circular = DMA_CIRCULAR,
		};

		/// <summary>
		///		数据传输模式。
		///		- 可以选择普通模式或循环模式。循环模式不能用于内存到内存传输模式。
		/// </summary>
		Mode _mode;

		enum class Priority
		{
			Low = DMA_PRIORITY_LOW,
			Medium = DMA_PRIORITY_MEDIUM,
			High = DMA_PRIORITY_HIGH,
			VeryHigh = DMA_PRIORITY_VERY_HIGH,
		};

		/// <summary>
		///		此通道的传输优先级。
		/// </summary>
		Priority _priority;
	};
}
