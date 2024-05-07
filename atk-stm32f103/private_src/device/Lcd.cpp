#include"Lcd.h"
#include<atk-stm32f103/bsp.h>

using namespace hal;
using namespace atk;

atk::Lcd::Lcd()
{
	InitGpio();
	__HAL_RCC_FSMC_CLK_ENABLE();

	_sram_handle.Instance = FSMC_NORSRAM_DEVICE;
	_sram_handle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;
	_sram_handle.Init = NorSramInitOptions();

	FSMC_NORSRAM_TimingTypeDef read_timing = ReadTiming();
	FSMC_NORSRAM_TimingTypeDef write_timing = WriteTiming();
	HAL_SRAM_Init(&_sram_handle, &read_timing, &write_timing);
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

constexpr volatile uint16_t *atk::Lcd::CommandAddress()
{
	constexpr uint32_t addr = (uint32_t)((0X60000000 + (0X4000000 * (4 - 1))) | (((1 << 10) * 2) - 2));
	return reinterpret_cast<uint16_t *>(addr);
}

constexpr volatile uint16_t *atk::Lcd::DataAddress()
{
	return CommandAddress() + 2;
}

void atk::Lcd::InitGpio()
{
	auto init_control_line = [&]()
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
	};

	auto init_data_bus = [&]()
	{
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
	};

	init_control_line();
	init_data_bus();
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

void atk::Lcd::TurnOnBackLight()
{
	BL_Port().DigitalWritePin(BL_Pin(), 1);
}

void atk::Lcd::TurnOffBackLight()
{
	BL_Port().DigitalWritePin(BL_Pin(), 0);
}

uint32_t atk::Lcd::LcdDriverChipId()
{
	uint16_t id = 0;
	WriteCommand(0X04);
	uint16_t temp = ReadData();	// 第一次读取会读取到刚刚写入的命令 0x04
	temp = ReadData();			// 读到 0x85
	temp = ReadData();			// 读到 0x85
	id = temp << 8;
	temp = ReadData();			// 读到 0x52
	id |= temp;
	return id;
}

void atk::Lcd::DisplayOn()
{
	BSP::Delayer().Delay(std::chrono::milliseconds{ 50 });
	WriteCommand(0x11);
	BSP::Delayer().Delay(std::chrono::milliseconds{ 120 });

	WriteCommand(0x36);
	WriteData(0x00);


	WriteCommand(0x3A);
	WriteData(0X05);

	WriteCommand(0xB2);
	WriteData(0x0C);
	WriteData(0x0C);
	WriteData(0x00);
	WriteData(0x33);
	WriteData(0x33);

	WriteCommand(0xB7);
	WriteData(0x35);

	WriteCommand(0xBB); /* vcom */
	WriteData(0x32);  /* 30 */

	WriteCommand(0xC0);
	WriteData(0x0C);

	WriteCommand(0xC2);
	WriteData(0x01);

	WriteCommand(0xC3); /* vrh */
	WriteData(0x10);  /* 17 0D */

	WriteCommand(0xC4); /* vdv */
	WriteData(0x20);  /* 20 */

	WriteCommand(0xC6);
	WriteData(0x0f);

	WriteCommand(0xD0);
	WriteData(0xA4);
	WriteData(0xA1);

	WriteCommand(0xE0); /* Set Gamma  */
	WriteData(0xd0);
	WriteData(0x00);
	WriteData(0x02);
	WriteData(0x07);
	WriteData(0x0a);
	WriteData(0x28);
	WriteData(0x32);
	WriteData(0X44);
	WriteData(0x42);
	WriteData(0x06);
	WriteData(0x0e);
	WriteData(0x12);
	WriteData(0x14);
	WriteData(0x17);


	WriteCommand(0XE1);  /* Set Gamma */
	WriteData(0xd0);
	WriteData(0x00);
	WriteData(0x02);
	WriteData(0x07);
	WriteData(0x0a);
	WriteData(0x28);
	WriteData(0x31);
	WriteData(0x54);
	WriteData(0x47);
	WriteData(0x0e);
	WriteData(0x1c);
	WriteData(0x17);
	WriteData(0x1b);
	WriteData(0x1e);


	WriteCommand(0x2A);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0xef);

	WriteCommand(0x2B);
	WriteData(0x00);
	WriteData(0x00);
	WriteData(0x01);
	WriteData(0x3f);

	WriteCommand(0x29); /* display on */
}

void atk::Lcd::Clear(Color color)
{
}
