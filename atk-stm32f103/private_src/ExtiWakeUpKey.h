#pragma once
#include <atomic>
#include <bsp-interface/di/gpio.h>
#include <bsp-interface/key/IEventDrivenKey.h>

namespace bsp
{
    /// @brief 外部中断驱动的按钮，按钮的丝印是 wake up。
    class ExtiWakeUpKey : public bsp::IEventDrivenKey
    {
    private:
        ExtiWakeUpKey();

        /// @brief 中断函数中经过消抖，确认按键被按下后就会将此字段赋值为 true。
        std::atomic_bool _is_pressed = false;
        bsp::IGpioPin *_pin = nullptr;

    public:
        static ExtiWakeUpKey &Instance()
        {
            static ExtiWakeUpKey instance;
            return instance;
        }

        bool IsPressed() override
        {
            return _is_pressed;
        }

        void ClearPressedFlag() override
        {
            _is_pressed = false;
        }
    };
} // namespace bsp
