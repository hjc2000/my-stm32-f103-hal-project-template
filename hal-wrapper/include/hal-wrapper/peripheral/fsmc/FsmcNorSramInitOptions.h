#pragma once
#include<hal.h>

namespace hal
{
	class FsmcNorSramInitOptions
	{
	public:
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

		uint32_t MemoryDataWidth;              /*!< Specifies the external memory device width.
		This parameter can be a value of @ref FSMC_NORSRAM_Data_Width            */

		uint32_t BurstAccessMode;              /*!< Enables or disables the burst access mode for Flash memory,
		valid only with synchronous burst Flash memories.
		This parameter can be a value of @ref FSMC_Burst_Access_Mode             */

		uint32_t WaitSignalPolarity;           /*!< Specifies the wait signal polarity, valid only when accessing
		the Flash memory in burst mode.
		This parameter can be a value of @ref FSMC_Wait_Signal_Polarity          */

		uint32_t WrapMode;                     /*!< Enables or disables the Wrapped burst access mode for Flash
		memory, valid only when accessing Flash memories in burst mode.
		This parameter can be a value of @ref FSMC_Wrap_Mode                     */

		uint32_t WaitSignalActive;             /*!< Specifies if the wait signal is asserted by the memory one
		clock cycle before the wait state or during the wait state,
		valid only when accessing memories in burst mode.
		This parameter can be a value of @ref FSMC_Wait_Timing                   */

		uint32_t WriteOperation;               /*!< Enables or disables the write operation in the selected device by the FSMC.
		This parameter can be a value of @ref FSMC_Write_Operation               */

		uint32_t WaitSignal;                   /*!< Enables or disables the wait state insertion via wait
		signal, valid for Flash memory access in burst mode.
		This parameter can be a value of @ref FSMC_Wait_Signal                   */

		uint32_t ExtendedMode;                 /*!< Enables or disables the extended mode.
		This parameter can be a value of @ref FSMC_Extended_Mode                 */

		uint32_t AsynchronousWait;             /*!< Enables or disables wait signal during asynchronous transfers,
		valid only with asynchronous Flash memories.
		This parameter can be a value of @ref FSMC_AsynchronousWait              */

		uint32_t WriteBurst;                   /*!< Enables or disables the write burst operation.
		This parameter can be a value of @ref FSMC_Write_Burst                   */


		uint32_t PageSize;                     /*!< Specifies the memory page size.
		This parameter can be a value of @ref FSMC_Page_Size                     */

		operator FSMC_NORSRAM_InitTypeDef() const;
	};
}
