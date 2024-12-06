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
    // _bl_pin
    {
        _bl_pin = DI_GpioPinCollection().Get("PB0");
        _bl_pin->OpenAsOutputMode(bsp::IGpioPinPullMode::NoPull, bsp::IGpioPinDriver::PushPull);
    }

    // _rd_pin
    {
        _rd_pin = DI_GpioPinCollection().Get("PD4");
        _rd_pin->OpenAsAlternateFunctionMode("af_input",
                                             bsp::IGpioPinPullMode::PullUp,
                                             bsp::IGpioPinDriver::PushPull);
    }

    // _wr_pin
    {
        _wr_pin = DI_GpioPinCollection().Get("PD5");
        _wr_pin->OpenAsAlternateFunctionMode("af_push_pull",
                                             bsp::IGpioPinPullMode::PullUp,
                                             bsp::IGpioPinDriver::PushPull);
    }

    // _cs_pin
    {
        _cs_pin = DI_GpioPinCollection().Get("PG12");
        _cs_pin->OpenAsAlternateFunctionMode("af_push_pull",
                                             bsp::IGpioPinPullMode::PullUp,
                                             bsp::IGpioPinDriver::PushPull);
    }

    // _rs_pin
    {
        _rs_pin = DI_GpioPinCollection().Get("PG0");
        _rs_pin->OpenAsAlternateFunctionMode("af_push_pull",
                                             bsp::IGpioPinPullMode::PullUp,
                                             bsp::IGpioPinDriver::PushPull);
    }

    char const *pin_names[] = {
        "PD0",
        "PD1",
        "PD8",
        "PD9",
        "PD10",
        "PD14",
        "PD15",
        "PE7",
        "PE8",
        "PE9",
        "PE10",
        "PE11",
        "PE12",
        "PE13",
        "PE14",
        "PE15",
    };

    for (char const *pin_name : pin_names)
    {
        DI_GpioPinCollection().Get(pin_name)->OpenAsAlternateFunctionMode("af_push_pull",
                                                                          bsp::IGpioPinPullMode::PullUp,
                                                                          bsp::IGpioPinDriver::PushPull);
    }
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
