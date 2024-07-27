#include "Lcd.h"
#include <base/Initializer.h>
#include <bsp/bsp.h>

using namespace bsp;
using namespace hal;

static base::Initializer _init{
	[]()
	{
		Lcd::Instance();
	}};

Lcd::Lcd() : bsp::ST7789LcdDriver(DI_Delayer())
{
	InitGpio();
	__HAL_RCC_FSMC_CLK_ENABLE();

	_sram_handle.Instance = FSMC_NORSRAM_DEVICE;
	_sram_handle.Extended = FSMC_NORSRAM_EXTENDED_DEVICE;

	hal::FsmcNorSramConfig nor_sram_init_options{};
	nor_sram_init_options.SetBank(hal::FsmcNorSramConfig::BankEnum::Bank4);
	nor_sram_init_options.SetDataAddressMux(hal::FsmcNorSramConfig::DataAddressMuxOption::Disable);
	nor_sram_init_options.SetMemoryType(hal::FsmcNorSramConfig::MemoryTypeEnum::SRSM);
	nor_sram_init_options.SetMemoryDataWidth(hal::FsmcNorSramConfig::MemoryDataWidthOption::Width16);
	nor_sram_init_options.SetBurstAccessMode(hal::FsmcNorSramConfig::BurstAccessModeOption::Disable);
	nor_sram_init_options.SetWaitSignalPolarity(hal::FsmcNorSramConfig::WaitSignalPolarityOption::Low);
	nor_sram_init_options.SetWrapMode(hal::FsmcNorSramConfig::WrapModeOption::Disable);
	nor_sram_init_options.SetWaitSignalActive(hal::FsmcNorSramConfig::WaitSignalActiveOption::BeforeWs);
	nor_sram_init_options.SetWriteOperation(hal::FsmcNorSramConfig::WriteOperationOption::Enable);
	nor_sram_init_options.SetWaitSignal(hal::FsmcNorSramConfig::WaitSignalOption::Disable);
	nor_sram_init_options.SetExtendedMode(hal::FsmcNorSramConfig::ExtendedModeOption::Enable);
	nor_sram_init_options.SetAsynchronousWait(hal::FsmcNorSramConfig::AsynchronousWaitOption::Disable);
	nor_sram_init_options.SetWriteBurst(hal::FsmcNorSramConfig::WriteBurstOption::Disable);
	nor_sram_init_options.SetPageSize(hal::FsmcNorSramConfig::PageSizeOption::SizeNone);
	_sram_handle.Init = nor_sram_init_options.Handle();

	hal::FsmcNorSramTiming read_timing{};
	read_timing.SetAccessMode(hal::FsmcNorSramTiming::AccessModeOption::ModeA);
	read_timing.SetAddressSetupTime(0);
	read_timing.SetAddressHoldTime(0);
	read_timing.SetDataSetupTime(15);

	hal::FsmcNorSramTiming write_timing{};
	write_timing.SetAccessMode(hal::FsmcNorSramTiming::AccessModeOption::ModeA);
	write_timing.SetAddressSetupTime(0);
	write_timing.SetAddressHoldTime(0);
	write_timing.SetDataSetupTime(1);
	HAL_SRAM_Init(&_sram_handle, read_timing, write_timing);
}

void Lcd::InitGpio()
{
	auto init_control_line = [&]()
	{
		RD_Port().EnableClock();
		WR_Port().EnableClock();
		BL_Port().EnableClock();
		CS_Port().EnableClock();
		RS_Port().EnableClock();

		GpioPinConfig gpio_init_options;
		gpio_init_options.SetMode(hal::GpioPinConfig::ModeOption::AlternateFunction_PushPull);
		gpio_init_options.SetPull(hal::GpioPinConfig::PullOption::PullUp);
		gpio_init_options.SetSpeed(hal::GpioPinConfig::SpeedOption::High);

		gpio_init_options.SetPin(RD_Pin());
		RD_Port().InitPin(gpio_init_options);

		gpio_init_options.SetPin(WR_Pin());
		WR_Port().InitPin(gpio_init_options);

		gpio_init_options.SetPin(CS_Pin());
		CS_Port().InitPin(gpio_init_options);

		gpio_init_options.SetPin(RS_Pin());
		RS_Port().InitPin(gpio_init_options);

		gpio_init_options.SetPin(BL_Pin());
		gpio_init_options.SetMode(hal::GpioPinConfig::ModeOption::Output_PushPull);
		BL_Port().InitPin(gpio_init_options);
	};

	auto init_data_bus = [&]()
	{
		GpioPortD::Instance().EnableClock();
		GpioPortE::Instance().EnableClock();

		GpioPinConfig options;
		options.SetMode(hal::GpioPinConfig::ModeOption::AlternateFunction_PushPull);
		options.SetPull(hal::GpioPinConfig::PullOption::PullUp);
		options.SetSpeed(hal::GpioPinConfig::SpeedOption::High);

		options.SetPin(
			hal::GpioPinConfig::PinEnum::Pin0 | hal::GpioPinConfig::PinEnum::Pin1 | hal::GpioPinConfig::PinEnum::Pin8 | hal::GpioPinConfig::PinEnum::Pin9 | hal::GpioPinConfig::PinEnum::Pin10 | hal::GpioPinConfig::PinEnum::Pin14 | hal::GpioPinConfig::PinEnum::Pin15);
		GpioPortD::Instance().InitPin(options);

		options.SetPin(
			hal::GpioPinConfig::PinEnum::Pin7 | hal::GpioPinConfig::PinEnum::Pin8 | hal::GpioPinConfig::PinEnum::Pin9 | hal::GpioPinConfig::PinEnum::Pin10 | hal::GpioPinConfig::PinEnum::Pin11 | hal::GpioPinConfig::PinEnum::Pin12 | hal::GpioPinConfig::PinEnum::Pin13 | hal::GpioPinConfig::PinEnum::Pin14 | hal::GpioPinConfig::PinEnum::Pin15);
		GpioPortE::Instance().InitPin(options);
	};

	init_control_line();
	init_data_bus();
}

void Lcd::WriteCommand(uint16_t cmd)
{
	*CommandAddress() = cmd;
}

void Lcd::WriteCommand(uint16_t cmd, uint16_t param)
{
	WriteCommand(cmd);
	WriteData(param);
}

void Lcd::WriteData(uint16_t data)
{
	*DataAddress() = data;
}

uint16_t Lcd::ReadData()
{
	return *DataAddress();
}

void Lcd::TurnOnBackLight()
{
	BL_Port().DigitalWritePin(BL_Pin(), 1);
}

void Lcd::TurnOffBackLight()
{
	BL_Port().DigitalWritePin(BL_Pin(), 0);
}
