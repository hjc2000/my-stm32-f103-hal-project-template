#pragma once
#include<base/HandleWrapper.h>
#include<hal.h>

namespace hal
{
	class FsmcNorSramConfig :
		public base::HandleWrapper<FSMC_NORSRAM_InitTypeDef>
	{
	private:
		FSMC_NORSRAM_InitTypeDef _handle { };

	public:
		FSMC_NORSRAM_InitTypeDef &Handle() override
		{
			return _handle;
		}

		enum class BankEnum
		{
			Bank1 = FSMC_NORSRAM_BANK1,
			Bank2 = FSMC_NORSRAM_BANK2,
			Bank3 = FSMC_NORSRAM_BANK3,
			Bank4 = FSMC_NORSRAM_BANK4,
		};

		BankEnum Bank() const
		{
			return static_cast<BankEnum>(_handle.NSBank);
		}
		void SetBank(BankEnum value)
		{
			_handle.NSBank = static_cast<uint32_t>(value);
		}

		enum class DataAddressMuxOption
		{
			Disable = FSMC_DATA_ADDRESS_MUX_DISABLE,
			Enable = FSMC_DATA_ADDRESS_MUX_ENABLE,
		};

		/// <summary>
		///		地址总线和数据总线是否复用，即数据和地址全部通过 FSMC 的数据总线进行传输。
		/// </summary>
		DataAddressMuxOption DataAddressMux() const
		{
			return static_cast<DataAddressMuxOption>(_handle.DataAddressMux);
		}
		void SetDataAddressMux(DataAddressMuxOption value)
		{
			_handle.DataAddressMux = static_cast<uint32_t>(value);
		}

		enum class MemoryTypeEnum
		{
			SRSM = FSMC_MEMORY_TYPE_SRAM,
			PSRAM = FSMC_MEMORY_TYPE_PSRAM,
			NOR = FSMC_MEMORY_TYPE_NOR,
		};

		MemoryTypeEnum MemoryType() const
		{
			return static_cast<MemoryTypeEnum>(_handle.MemoryType);
		}
		void SetMemoryType(MemoryTypeEnum value)
		{
			_handle.MemoryType = static_cast<uint32_t>(value);
		}

		enum class MemoryDataWidthOption
		{
			Width8 = FSMC_NORSRAM_MEM_BUS_WIDTH_8,
			Width16 = FSMC_NORSRAM_MEM_BUS_WIDTH_16,
			Width32 = FSMC_NORSRAM_MEM_BUS_WIDTH_32,
		};

		MemoryDataWidthOption MemoryDataWidth() const
		{
			return static_cast<MemoryDataWidthOption>(_handle.MemoryDataWidth);
		}
		void SetMemoryDataWidth(MemoryDataWidthOption value)
		{
			_handle.MemoryDataWidth = static_cast<uint32_t>(value);
		}

		enum class BurstAccessModeOption
		{
			Disable = FSMC_BURST_ACCESS_MODE_DISABLE,
			Enable = FSMC_BURST_ACCESS_MODE_ENABLE,
		};

		BurstAccessModeOption BurstAccessMode() const
		{
			return static_cast<BurstAccessModeOption>(_handle.BurstAccessMode);
		}
		void SetBurstAccessMode(BurstAccessModeOption value)
		{
			_handle.BurstAccessMode = static_cast<uint32_t>(value);
		}

		enum class WaitSignalPolarityOption
		{
			Low = FSMC_WAIT_SIGNAL_POLARITY_LOW,
			High = FSMC_WAIT_SIGNAL_POLARITY_HIGH,
		};

		WaitSignalPolarityOption WaitSignalPolarity() const
		{
			return static_cast<WaitSignalPolarityOption>(_handle.WaitSignalPolarity);
		}
		void SetWaitSignalPolarity(WaitSignalPolarityOption value)
		{
			_handle.WaitSignalPolarity = static_cast<uint32_t>(value);
		}

		enum class WrapModeOption
		{
			Disable = FSMC_WRAP_MODE_DISABLE,
			Enable = FSMC_WRAP_MODE_ENABLE,
		};

		WrapModeOption WrapMode() const
		{
			return static_cast<WrapModeOption>(_handle.WrapMode);
		}
		void SetWrapMode(WrapModeOption value)
		{
			_handle.WrapMode = static_cast<uint32_t>(value);
		}

		enum class WaitSignalActiveOption
		{
			BeforeWs = FSMC_WAIT_TIMING_BEFORE_WS,
			DuringWs = FSMC_WAIT_TIMING_DURING_WS,
		};

		WaitSignalActiveOption WaitSignalActive() const
		{
			return static_cast<WaitSignalActiveOption>(_handle.WaitSignalActive);
		}
		void SetWaitSignalActive(WaitSignalActiveOption value)
		{
			_handle.WaitSignalActive = static_cast<uint32_t>(value);
		}

		enum class WriteOperationOption
		{
			Disable = FSMC_WRITE_OPERATION_DISABLE,
			Enable = FSMC_WRITE_OPERATION_ENABLE,
		};

		WriteOperationOption WriteOperation() const
		{
			return static_cast<WriteOperationOption>(_handle.WriteOperation);
		}
		void SetWriteOperation(WriteOperationOption value)
		{
			_handle.WriteOperation = static_cast<uint32_t>(value);
		}

		enum class WaitSignalOption
		{
			Disable = FSMC_WAIT_SIGNAL_DISABLE,
			Enable = FSMC_WAIT_SIGNAL_ENABLE,
		};

		WaitSignalOption WaitSignal() const
		{
			return static_cast<WaitSignalOption>(_handle.WaitSignal);
		}
		void SetWaitSignal(WaitSignalOption value)
		{
			_handle.WaitSignal = static_cast<uint32_t>(value);
		}

		enum class ExtendedModeOption
		{
			Disable = FSMC_EXTENDED_MODE_DISABLE,
			Enable = FSMC_EXTENDED_MODE_ENABLE,
		};

		ExtendedModeOption ExtendedMode() const
		{
			return static_cast<ExtendedModeOption>(_handle.ExtendedMode);
		}
		void SetExtendedMode(ExtendedModeOption value)
		{
			_handle.ExtendedMode = static_cast<uint32_t>(value);
		}

		enum class AsynchronousWaitOption
		{
			Disable = FSMC_ASYNCHRONOUS_WAIT_DISABLE,
			Enable = FSMC_ASYNCHRONOUS_WAIT_ENABLE,
		};

		AsynchronousWaitOption AsynchronousWait() const
		{
			return static_cast<AsynchronousWaitOption>(_handle.AsynchronousWait);
		}
		void SetAsynchronousWait(AsynchronousWaitOption value)
		{
			_handle.AsynchronousWait = static_cast<uint32_t>(value);
		}

		enum class WriteBurstOption
		{
			Disable = FSMC_WRITE_BURST_DISABLE,
			Enable = FSMC_WRITE_BURST_ENABLE,
		};

		WriteBurstOption WriteBurst() const
		{
			return static_cast<WriteBurstOption>(_handle.WriteBurst);
		}
		void SetWriteBurst(WriteBurstOption value)
		{
			_handle.WriteBurst = static_cast<uint32_t>(value);
		}

		enum class PageSizeOption
		{
			SizeNone = FSMC_PAGE_SIZE_NONE,
			Size128 = FSMC_PAGE_SIZE_128,
			Size256 = FSMC_PAGE_SIZE_256,
			Size512 = FSMC_PAGE_SIZE_512,
			Size1024 = FSMC_PAGE_SIZE_1024,
		};

		PageSizeOption PageSize() const
		{
			return static_cast<PageSizeOption>(_handle.PageSize);
		}
		void SetPageSize(PageSizeOption value)
		{
			_handle.PageSize = static_cast<uint32_t>(value);
		}
	};
}
