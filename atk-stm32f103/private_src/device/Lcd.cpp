#include"Lcd.h"
#include<atk-stm32f103/bsp.h>

using namespace hal;
using namespace atk;

atk::Lcd::Lcd()
{
	InitGpio();
	_sram_handle.Instance = FSMC_NORSRAM_DEVICE;
	_sram_handle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
	_sram_handle.Init = NorSramInitOptions();
	_sram_handle.MspInitCallback = MspInitCallback;

	FSMC_NORSRAM_TimingTypeDef read_timing = ReadTiming();
	FSMC_NORSRAM_TimingTypeDef write_timing = WriteTiming();
	HAL_SRAM_Init(&_sram_handle, &read_timing, &write_timing);
	BSP::Delayer().Delay(std::chrono::milliseconds{ 50 });
}

void atk::Lcd::MspInitCallback(SRAM_HandleTypeDef *handle)
{
	__HAL_RCC_FSMC_CLK_ENABLE();
	hal::GpioPortD::Instance().EnableClock();
	hal::GpioPortE::Instance().EnableClock();

	hal::GpioPinInitOptions options;
	options._mode = GpioPinMode::AlternateFunction_PushPull;
	options._pull_mode = GpioPinPull::PullUp;
	options._speed = GpioPinSpeed::High;

	hal::GpioPortD::Instance().InitPin(GpioPin::Pin0, options);
	hal::GpioPortD::Instance().InitPin(GpioPin::Pin1, options);
	hal::GpioPortD::Instance().InitPin(GpioPin::Pin8, options);
	hal::GpioPortD::Instance().InitPin(GpioPin::Pin9, options);
	hal::GpioPortD::Instance().InitPin(GpioPin::Pin10, options);
	hal::GpioPortD::Instance().InitPin(GpioPin::Pin14, options);
	hal::GpioPortD::Instance().InitPin(GpioPin::Pin15, options);

	hal::GpioPortE::Instance().InitPin(GpioPin::Pin7, options);
	hal::GpioPortE::Instance().InitPin(GpioPin::Pin8, options);
	hal::GpioPortE::Instance().InitPin(GpioPin::Pin9, options);
	hal::GpioPortE::Instance().InitPin(GpioPin::Pin10, options);
	hal::GpioPortE::Instance().InitPin(GpioPin::Pin11, options);
	hal::GpioPortE::Instance().InitPin(GpioPin::Pin12, options);
	hal::GpioPortE::Instance().InitPin(GpioPin::Pin13, options);
	hal::GpioPortE::Instance().InitPin(GpioPin::Pin14, options);
	hal::GpioPortE::Instance().InitPin(GpioPin::Pin15, options);
}

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
	nor_sram_init_options._memory_type = FsmcNorSramInitOptions::MemoryType::SRSM;
	nor_sram_init_options._memory_data_width = FsmcNorSramInitOptions::MemoryDataWidth::Width16;
	nor_sram_init_options._burst_access_mode = FsmcNorSramInitOptions::BurstAccessMode::Disable;
	nor_sram_init_options._wait_signal_polarity = FsmcNorSramInitOptions::WaitSignalPolarity::Low;
	nor_sram_init_options._wrap_mode = FsmcNorSramInitOptions::WrapMode::Disable;
	nor_sram_init_options._wait_signal_active = FsmcNorSramInitOptions::WaitSignalActive::BeforeWs;
	nor_sram_init_options._write_operation = FsmcNorSramInitOptions::WriteOperation::Enable;
	nor_sram_init_options._wait_signal = FsmcNorSramInitOptions::WaitSignal::Disable;
	nor_sram_init_options._extended_mode = FsmcNorSramInitOptions::ExtendedMode::Enable;
	nor_sram_init_options._asynchronous_wait = FsmcNorSramInitOptions::AsynchronousWait::Disable;
	nor_sram_init_options._write_burst = FsmcNorSramInitOptions::WriteBurst::Disable;
	nor_sram_init_options._page_size = FsmcNorSramInitOptions::PageSize::SizeNone;
	return nor_sram_init_options;
}

constexpr uint16_t *atk::Lcd::CommandAddress()
{
	constexpr uint32_t addr = (uint32_t)((0X60000000 + (0X4000000 * (4 - 1))) | (((1 << 10) * 2) - 2));
	return reinterpret_cast<uint16_t *>(addr);
}

constexpr uint16_t *atk::Lcd::DataAddress()
{
	return CommandAddress() + 2;
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

void atk::Lcd::TurnOnBackLight()
{
	BL_Port().DigitalWritePin(BL_Pin(), 1);
}

void atk::Lcd::TurnOffBackLight()
{
	BL_Port().DigitalWritePin(BL_Pin(), 0);
}

void atk::Lcd::WriteCommand(uint16_t cmd)
{
	*CommandAddress() = cmd;
}

void atk::Lcd::WriteCommand(uint16_t cmd, uint16_t param)
{
	WriteCommand(cmd);
	WriteData(param);
}

void atk::Lcd::WriteData(uint16_t data)
{
	*DataAddress() = data;
}

uint16_t atk::Lcd::ReadData()
{
	return *DataAddress();
}
