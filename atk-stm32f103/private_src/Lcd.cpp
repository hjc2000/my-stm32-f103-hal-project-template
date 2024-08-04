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
		// _bl_pin
		{
			auto options = DICreate_GpioPinOptions();
			options->SetDirection(bsp::IGpioPinDirection::Output);
			options->SetDriver(bsp::IGpioPinDriver::PushPull);
			options->SetPullMode(bsp::IGpioPinPullMode::NoPull);
			options->SetSpeedLevel(2);
			options->SetWorkMode(bsp::IGpioPinWorkMode::Gpio);
			_bl_pin = DI_GpioPinCollection().Get("PB0");
			_bl_pin->Open(*options);
		}

		// _rd_pin
		{
			auto options = DICreate_GpioPinOptions();
			options->SetAlternateFunction("af_input");
			options->SetDirection(bsp::IGpioPinDirection::Input);
			options->SetPullMode(bsp::IGpioPinPullMode::PullUp);
			options->SetSpeedLevel(2);
			options->SetWorkMode(bsp::IGpioPinWorkMode::AlternateFunction);
			_rd_pin = DI_GpioPinCollection().Get("PD4");
			_rd_pin->Open(*options);
		}

		// _wr_pin
		{
			auto options = DICreate_GpioPinOptions();
			options->SetAlternateFunction("af_push_pull");
			options->SetDirection(bsp::IGpioPinDirection::Output);
			options->SetDriver(bsp::IGpioPinDriver::PushPull);
			options->SetPullMode(bsp::IGpioPinPullMode::PullUp);
			options->SetSpeedLevel(2);
			options->SetWorkMode(bsp::IGpioPinWorkMode::AlternateFunction);
			_wr_pin = DI_GpioPinCollection().Get("PD5");
			_wr_pin->Open(*options);
		}

		// _cs_pin
		{
			auto options = DICreate_GpioPinOptions();
			options->SetAlternateFunction("af_push_pull");
			options->SetDirection(bsp::IGpioPinDirection::Output);
			options->SetDriver(bsp::IGpioPinDriver::PushPull);
			options->SetPullMode(bsp::IGpioPinPullMode::PullUp);
			options->SetSpeedLevel(2);
			options->SetWorkMode(bsp::IGpioPinWorkMode::AlternateFunction);
			_cs_pin = DI_GpioPinCollection().Get("PG12");
			_cs_pin->Open(*options);
		}

		// _rs_pin
		{
			auto options = DICreate_GpioPinOptions();
			options->SetAlternateFunction("af_push_pull");
			options->SetDirection(bsp::IGpioPinDirection::Output);
			options->SetDriver(bsp::IGpioPinDriver::PushPull);
			options->SetPullMode(bsp::IGpioPinPullMode::PullUp);
			options->SetSpeedLevel(2);
			options->SetWorkMode(bsp::IGpioPinWorkMode::AlternateFunction);
			_rs_pin = DI_GpioPinCollection().Get("PG0");
			_rs_pin->Open(*options);
		}
	};

	auto init_data_bus = [&]()
	{
		GpioPortD::Instance().EnableClock();
		GpioPortE::Instance().EnableClock();

		GpioPinConfig options;
		options.SetMode(hal::GpioPinConfig::ModeOption::AlternateFunction_PushPull);
		options.SetPull(hal::GpioPinConfig::PullOption::PullUp);
		options.SetSpeed(hal::GpioPinConfig::SpeedOption::High);

		options.SetPin(hal::GpioPinConfig::PinEnum::Pin0 |
					   hal::GpioPinConfig::PinEnum::Pin1 |
					   hal::GpioPinConfig::PinEnum::Pin8 |
					   hal::GpioPinConfig::PinEnum::Pin9 |
					   hal::GpioPinConfig::PinEnum::Pin10 |
					   hal::GpioPinConfig::PinEnum::Pin14 |
					   hal::GpioPinConfig::PinEnum::Pin15);

		GpioPortD::Instance().InitPin(options);

		options.SetPin(
			hal::GpioPinConfig::PinEnum::Pin7 |
			hal::GpioPinConfig::PinEnum::Pin8 |
			hal::GpioPinConfig::PinEnum::Pin9 |
			hal::GpioPinConfig::PinEnum::Pin10 |
			hal::GpioPinConfig::PinEnum::Pin11 |
			hal::GpioPinConfig::PinEnum::Pin12 |
			hal::GpioPinConfig::PinEnum::Pin13 |
			hal::GpioPinConfig::PinEnum::Pin14 |
			hal::GpioPinConfig::PinEnum::Pin15);

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
	_bl_pin->WritePin(1);
}

void Lcd::TurnOffBackLight()
{
	_bl_pin->WritePin(0);
}
