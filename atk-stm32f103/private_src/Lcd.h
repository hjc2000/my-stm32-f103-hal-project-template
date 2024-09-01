#pragma once
#include <base/SingletonGetter.h>
#include <bsp-interface/di/gpio.h>
#include <bsp-interface/di/interrupt.h>
#include <bsp-interface/lcd/ST7789LcdDriver.h>
#include <hal-wrapper/peripheral/fsmc/FsmcNorSramConfig.h>
#include <hal-wrapper/peripheral/fsmc/FsmcNorSramTiming.h>
#include <stdexcept>

namespace bsp
{
    class Lcd :
        public bsp::ST7789LcdDriver
    {
    private:
        Lcd();

        SRAM_HandleTypeDef _sram_handle;

#pragma region 连接到 LCD 的 GPIO 引脚
        /// @brief 连接 LCD 的 RD 引脚
        bsp::IGpioPin *_rd_pin = nullptr;

        /// @brief 连接 LCD 的 WR 引脚
        bsp::IGpioPin *_wr_pin = nullptr;

        /// @brief 连接 LCD 的 BL 引脚。这是控制背光的。
        bsp::IGpioPin *_bl_pin = nullptr;

        /// @brief 连接 LCD 的 CS 引脚。这是片选。
        bsp::IGpioPin *_cs_pin = nullptr;

        /// @brief 连接到 LCD 的 RS 引脚。
        bsp::IGpioPin *_rs_pin = nullptr;
#pragma endregion

        uint16_t volatile *CommandAddress()
        {
            constexpr uint32_t addr = (uint32_t)((0X60000000 + (0X4000000 * (4 - 1))) | (((1 << 10) * 2) - 2));
            return reinterpret_cast<uint16_t *>(addr);
        }

        uint16_t volatile *DataAddress()
        {
            return CommandAddress() + 2;
        }

        void InitGpio();

    public:
        static Lcd &Instance()
        {
            class Getter : public base::SingletonGetter<Lcd>
            {
            public:
                std::unique_ptr<Lcd> Create() override
                {
                    return std::unique_ptr<Lcd>{new Lcd{}};
                }

                void Lock() override
                {
                    DI_InterruptSwitch().DisableGlobalInterrupt();
                }

                void Unlock() override
                {
                    DI_InterruptSwitch().EnableGlobalInterrupt();
                }
            };

            Getter g;
            return g.Instance();
        }

#pragma region ST7789LcdDriver
        void WriteCommand(uint16_t cmd) override;
        void WriteCommand(uint16_t cmd, uint16_t param) override;

        void WriteData(uint16_t data) override;
        uint16_t ReadData() override;

        void TurnOnBackLight() override;
        void TurnOffBackLight() override;
#pragma endregion
    };
} // namespace bsp
