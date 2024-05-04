#include"FsmcNorSramInitOptions.h"

hal::FsmcNorSramInitOptions::FsmcNorSramInitOptions(FSMC_NORSRAM_InitTypeDef const &o)
{
	*this = o;
}

hal::FsmcNorSramInitOptions &hal::FsmcNorSramInitOptions::operator=(FSMC_NORSRAM_InitTypeDef const &o)
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

hal::FsmcNorSramInitOptions::operator FSMC_NORSRAM_InitTypeDef() const
{
	FSMC_NORSRAM_InitTypeDef o;
	return o;
}
