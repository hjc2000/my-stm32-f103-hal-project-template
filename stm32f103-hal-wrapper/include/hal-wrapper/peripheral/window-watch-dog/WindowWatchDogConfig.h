#pragma once
#include <hal.h>

namespace hal
{
    /// @brief 窗口看门狗初始化选项。
    class WindowWatchDogConfig
    {
    private:
        WWDG_InitTypeDef _handle{};

    public:
        WindowWatchDogConfig() = default;
        WindowWatchDogConfig(WindowWatchDogConfig const &o) = default;
        WindowWatchDogConfig(WWDG_InitTypeDef const &o);
        WindowWatchDogConfig &operator=(WindowWatchDogConfig const &o) = default;
        WindowWatchDogConfig &operator=(WWDG_InitTypeDef const &o);

        operator WWDG_InitTypeDef() const
        {
            return _handle;
        }

        enum class PrescalerOption
        {
            DIV1 = WWDG_PRESCALER_1,
            DIV2 = WWDG_PRESCALER_2,
            DIV4 = WWDG_PRESCALER_4,
            DIV8 = WWDG_PRESCALER_8,
        };

        PrescalerOption Prescaler() const;
        void SetPrescaler(PrescalerOption value);

        /// <summary>
        ///		窗口上界，范围：[0x40, 0x7F]
        ///		* 喂狗时间如果大于该值，会触发看门狗。
        /// </summary>
        uint32_t Window() const;
        void SetWindow(uint32_t value);

        /// <summary>
        ///		计数器重载值。
        ///		* 范围：[0x40, 0x7F]
        /// </summary>
        uint32_t CounterReloadValue() const;
        void SetCounterReloadValue(uint32_t value);

        enum class EarlyWakeupInterruptOption
        {
            Enable = WWDG_EWI_ENABLE,
            Disable = WWDG_EWI_DISABLE,
        };

        /// <summary>
        ///		选择看门狗即将超时时是否触发 “提早唤醒中断”。
        /// </summary>
        EarlyWakeupInterruptOption EarlyWakeupInterrupt() const;
        void SetEarlyWakeupInterrupt(EarlyWakeupInterruptOption value);
    };
} // namespace hal
