#pragma once
#include<hal.h>

namespace bsp
{
	class FsmcNorSramInitOptions
	{
	public:
		FsmcNorSramInitOptions() = default;
		FsmcNorSramInitOptions(FSMC_NORSRAM_InitTypeDef const &o);
		FsmcNorSramInitOptions &operator=(FSMC_NORSRAM_InitTypeDef const &o);
		operator FSMC_NORSRAM_InitTypeDef() const;

		enum class Bank
		{
			Bank1 = FSMC_NORSRAM_BANK1,
			Bank2 = FSMC_NORSRAM_BANK2,
			Bank3 = FSMC_NORSRAM_BANK3,
			Bank4 = FSMC_NORSRAM_BANK4,
		};

		Bank _bank;

		enum class DataAddressMux
		{
			Disable = FSMC_DATA_ADDRESS_MUX_DISABLE,
			Enable = FSMC_DATA_ADDRESS_MUX_ENABLE,
		};

		/// <summary>
		///		地址总线和数据总线是否复用，即数据和地址全部通过 FSMC 的数据总线进行传输。
		/// </summary>
		DataAddressMux _data_address_mux;

		enum class MemoryType
		{
			SRSM = FSMC_MEMORY_TYPE_SRAM,
			PSRAM = FSMC_MEMORY_TYPE_PSRAM,
			NOR = FSMC_MEMORY_TYPE_NOR,
		};

		MemoryType _memory_type;

		enum class MemoryDataWidth
		{
			Width8 = FSMC_NORSRAM_MEM_BUS_WIDTH_8,
			Width16 = FSMC_NORSRAM_MEM_BUS_WIDTH_16,
			Width32 = FSMC_NORSRAM_MEM_BUS_WIDTH_32,
		};

		MemoryDataWidth _memory_data_width;

		enum class BurstAccessMode
		{
			Disable = FSMC_BURST_ACCESS_MODE_DISABLE,
			Enable = FSMC_BURST_ACCESS_MODE_ENABLE,
		};

		BurstAccessMode _burst_access_mode;

		enum class WaitSignalPolarity
		{
			Low = FSMC_WAIT_SIGNAL_POLARITY_LOW,
			High = FSMC_WAIT_SIGNAL_POLARITY_HIGH,
		};

		WaitSignalPolarity _wait_signal_polarity;

		enum class WrapMode
		{
			Disable = FSMC_WRAP_MODE_DISABLE,
			Enable = FSMC_WRAP_MODE_ENABLE,
		};

		WrapMode _wrap_mode;

		enum class WaitSignalActive
		{
			BeforeWs = FSMC_WAIT_TIMING_BEFORE_WS,
			DuringWs = FSMC_WAIT_TIMING_DURING_WS,
		};

		WaitSignalActive _wait_signal_active;

		enum class WriteOperation
		{
			Disable = FSMC_WRITE_OPERATION_DISABLE,
			Enable = FSMC_WRITE_OPERATION_ENABLE,
		};

		WriteOperation _write_operation;

		enum class WaitSignal
		{
			Disable = FSMC_WAIT_SIGNAL_DISABLE,
			Enable = FSMC_WAIT_SIGNAL_ENABLE,
		};

		WaitSignal _wait_signal;

		enum class ExtendedMode
		{
			Disable = FSMC_EXTENDED_MODE_DISABLE,
			Enable = FSMC_EXTENDED_MODE_ENABLE,
		};

		ExtendedMode _extended_mode;

		enum class AsynchronousWait
		{
			Disable = FSMC_ASYNCHRONOUS_WAIT_DISABLE,
			Enable = FSMC_ASYNCHRONOUS_WAIT_ENABLE,
		};

		AsynchronousWait _asynchronous_wait;

		enum class WriteBurst
		{
			Disable = FSMC_WRITE_BURST_DISABLE,
			Enable = FSMC_WRITE_BURST_ENABLE,
		};

		WriteBurst _write_burst;

		enum class PageSize
		{
			SizeNone = FSMC_PAGE_SIZE_NONE,
			Size128 = FSMC_PAGE_SIZE_128,
			Size256 = FSMC_PAGE_SIZE_256,
			Size512 = FSMC_PAGE_SIZE_512,
			Size1024 = FSMC_PAGE_SIZE_1024,
		};

		PageSize _page_size;
	};
}
