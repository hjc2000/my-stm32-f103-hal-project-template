#include"FsmcNorSramInitOptions.h"

bsp::FsmcNorSramInitOptions::FsmcNorSramInitOptions(FSMC_NORSRAM_InitTypeDef const &o)
{
	*this = o;
}

bsp::FsmcNorSramInitOptions &bsp::FsmcNorSramInitOptions::operator=(FSMC_NORSRAM_InitTypeDef const &o)
{
	_bank = static_cast<Bank>(o.NSBank);
	_data_address_mux = static_cast<DataAddressMux>(o.DataAddressMux);
	_memory_type = static_cast<MemoryType>(o.MemoryType);
	_memory_data_width = static_cast<MemoryDataWidth>(o.MemoryDataWidth);
	_burst_access_mode = static_cast<BurstAccessMode>(o.BurstAccessMode);
	_wait_signal_polarity = static_cast<WaitSignalPolarity>(o.WaitSignalPolarity);
	_wrap_mode = static_cast<WrapMode>(o.WrapMode);
	_wait_signal_active = static_cast<WaitSignalActive>(o.WaitSignalActive);
	_write_operation = static_cast<WriteOperation>(o.WriteOperation);
	_wait_signal = static_cast<WaitSignal>(o.WaitSignal);
	_extended_mode = static_cast<ExtendedMode>(o.ExtendedMode);
	_asynchronous_wait = static_cast<AsynchronousWait>(o.AsynchronousWait);
	_write_burst = static_cast<WriteBurst>(o.WriteBurst);
	_page_size = static_cast<PageSize>(o.PageSize);
	return *this;
}

bsp::FsmcNorSramInitOptions::operator FSMC_NORSRAM_InitTypeDef() const
{
	FSMC_NORSRAM_InitTypeDef o;
	o.NSBank = static_cast<uint32_t>(_bank);
	o.DataAddressMux = static_cast<uint32_t>(_data_address_mux);
	o.MemoryType = static_cast<uint32_t>(_memory_type);
	o.MemoryDataWidth = static_cast<uint32_t>(_memory_data_width);
	o.BurstAccessMode = static_cast<uint32_t>(_burst_access_mode);
	o.WaitSignalPolarity = static_cast<uint32_t>(_wait_signal_polarity);
	o.WrapMode = static_cast<uint32_t>(_wrap_mode);
	o.WaitSignalActive = static_cast<uint32_t>(_wait_signal_active);
	o.WriteOperation = static_cast<uint32_t>(_write_operation);
	o.WaitSignal = static_cast<uint32_t>(_wait_signal);
	o.ExtendedMode = static_cast<uint32_t>(_extended_mode);
	o.AsynchronousWait = static_cast<uint32_t>(_asynchronous_wait);
	o.WriteBurst = static_cast<uint32_t>(_write_burst);
	o.PageSize = static_cast<uint32_t>(_page_size);
	return o;
}
