#include "Lcd.h"
#include <bsp/bsp.h>

using namespace bsp;
using namespace hal;

Lcd::Lcd()
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
    _sram_handle.Init = nor_sram_init_options;

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
    HAL_SRAM_Init(&_sram_handle, &read_timing._handle, &write_timing._handle);
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
        auto options = DICreate_GpioPinOptions();
        options->SetAlternateFunction("af_push_pull");
        options->SetDirection(bsp::IGpioPinDirection::Output);
        options->SetDriver(bsp::IGpioPinDriver::PushPull);
        options->SetSpeedLevel(2);
        options->SetWorkMode(bsp::IGpioPinWorkMode::AlternateFunction);

        DI_GpioPinCollection().Get("PD0")->Open(*options);
        DI_GpioPinCollection().Get("PD1")->Open(*options);
        DI_GpioPinCollection().Get("PD8")->Open(*options);
        DI_GpioPinCollection().Get("PD9")->Open(*options);
        DI_GpioPinCollection().Get("PD10")->Open(*options);
        DI_GpioPinCollection().Get("PD14")->Open(*options);
        DI_GpioPinCollection().Get("PD15")->Open(*options);

        DI_GpioPinCollection().Get("PE7")->Open(*options);
        DI_GpioPinCollection().Get("PE8")->Open(*options);
        DI_GpioPinCollection().Get("PE9")->Open(*options);
        DI_GpioPinCollection().Get("PE10")->Open(*options);
        DI_GpioPinCollection().Get("PE11")->Open(*options);
        DI_GpioPinCollection().Get("PE12")->Open(*options);
        DI_GpioPinCollection().Get("PE13")->Open(*options);
        DI_GpioPinCollection().Get("PE14")->Open(*options);
        DI_GpioPinCollection().Get("PE15")->Open(*options);
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
