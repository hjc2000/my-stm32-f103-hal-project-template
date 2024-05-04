#include"FsmcTiming.h"

hal::FsmcNorSramTiming::FsmcNorSramTiming(FSMC_NORSRAM_TimingTypeDef const &o)
{
	*this = o;
}

hal::FsmcNorSramTiming &hal::FsmcNorSramTiming::operator=(FSMC_NORSRAM_TimingTypeDef const &o)
{
	_address_setup_time = o.AddressSetupTime;
	_address_hold_time = o.AddressHoldTime;
	_data_setup_time = o.DataSetupTime;
	_bus_turn_around_duration = o.BusTurnAroundDuration;
	_clk_division = o.CLKDivision;
	_data_latency = o.DataLatency;
	_access_mode = static_cast<AccessMode>(o.AccessMode);
	return *this;
}

hal::FsmcNorSramTiming::operator FSMC_NORSRAM_TimingTypeDef() const
{
	FSMC_NORSRAM_TimingTypeDef o;
	o.AddressSetupTime = _address_setup_time;
	o.AddressHoldTime = _address_hold_time;
	o.DataSetupTime = _data_setup_time;
	o.BusTurnAroundDuration = _bus_turn_around_duration;
	o.CLKDivision = _clk_division;
	o.DataLatency = _data_latency;
	o.AccessMode = static_cast<uint32_t>(_access_mode);
	return o;
}
