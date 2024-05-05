#include"Lcd.h"

using namespace hal;
using namespace atk;

constexpr hal::FsmcNorSramTiming atk::Lcd::ReadTiming()
{
	hal::FsmcNorSramTiming read_timing;
	read_timing._access_mode = hal::FsmcNorSramTiming::AccessMode::ModeA;
	read_timing._address_setup_time = 0;
	read_timing._address_hold_time = 0;
	read_timing._data_setup_time = 15;
	return read_timing;
}

constexpr hal::FsmcNorSramTiming atk::Lcd::WriteTiming()
{
	hal::FsmcNorSramTiming write_timing;
	write_timing._access_mode = hal::FsmcNorSramTiming::AccessMode::ModeA;
	write_timing._address_setup_time = 0;
	write_timing._address_hold_time = 0;
	write_timing._data_setup_time = 1;
	return write_timing;
}

constexpr hal::FsmcNorSramInitOptions atk::Lcd::NorSramInitOptions()
{
	hal::FsmcNorSramInitOptions nor_sram_init_options;
	nor_sram_init_options._bank = FsmcNorSramInitOptions::Bank::Bank4;
	nor_sram_init_options._data_address_mux = FsmcNorSramInitOptions::DataAddressMux::Disable;
	nor_sram_init_options._memory_data_width = FsmcNorSramInitOptions::MemoryDataWidth::Width16;
	nor_sram_init_options._burst_access_mode = FsmcNorSramInitOptions::BurstAccessMode::Disable;
	nor_sram_init_options._wait_signal_polarity = FsmcNorSramInitOptions::WaitSignalPolarity::Low;
	nor_sram_init_options._wait_signal_active = FsmcNorSramInitOptions::WaitSignalActive::BeforeWs;
	nor_sram_init_options._write_operation = FsmcNorSramInitOptions::WriteOperation::Enable;
	nor_sram_init_options._wait_signal = FsmcNorSramInitOptions::WaitSignal::Disable;
	nor_sram_init_options._extended_mode = FsmcNorSramInitOptions::ExtendedMode::Enable;
	nor_sram_init_options._asynchronous_wait = FsmcNorSramInitOptions::AsynchronousWait::Disable;
	nor_sram_init_options._write_burst = FsmcNorSramInitOptions::WriteBurst::Disable;
	return nor_sram_init_options;
}

void atk::Lcd::InitGpio()
{
	RD_Port().EnableClock();
	WR_Port().EnableClock();
	BL_Port().EnableClock();
	CS_Port().EnableClock();
	RS_Port().EnableClock();

	hal::GpioPinInitOptions gpio_init_options;
	gpio_init_options._mode = GpioPinMode::AlternateFunction_PushPull;
	gpio_init_options._pull_mode = GpioPinPull::PullUp;
	gpio_init_options._speed = GpioPinSpeed::High;
	RD_Port().InitPin(RD_Pin(), gpio_init_options);
	WR_Port().InitPin(WR_Pin(), gpio_init_options);
	CS_Port().InitPin(CS_Pin(), gpio_init_options);
	RS_Port().InitPin(RS_Pin(), gpio_init_options);

	gpio_init_options._mode = GpioPinMode::Output_PushPull;
	BL_Port().InitPin(BL_Pin(), gpio_init_options);
}

void atk::Lcd::InitSramHandle()
{
	_sram_handle.Instance = FSMC_NORSRAM_DEVICE;
	_sram_handle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
	_sram_handle.Init = NorSramInitOptions();
}
