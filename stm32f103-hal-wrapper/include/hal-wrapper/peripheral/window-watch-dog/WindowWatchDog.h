#pragma once
#include <functional>
#include <hal-wrapper/peripheral/window-watch-dog/WindowWatchDogConfig.h>

namespace hal
{
    class WindowWatchDog
    {
    private:
        /// <summary>
        ///		提早唤醒中断发生时触发的回调。
        ///		* 不需要喂狗，因为本类的实现是先喂狗后再回调此函数的。
        /// </summary>
        std::function<void()> _early_wakeup_interrupt_callback;

        static void OnMspInitCallback(WWDG_HandleTypeDef *handle);
        static void OnEarlyWakeUpInterruptCallback(WWDG_HandleTypeDef *handle);

    public:
        WWDG_HandleTypeDef _handle;

        static WindowWatchDog &Instance()
        {
            static WindowWatchDog o;
            return o;
        }

        WWDG_TypeDef *HardwareInstance();

        void Initialize(WindowWatchDogConfig &options);
        void Feed();
        void SetEarlyWakeupInterruptCallback(std::function<void()> func);
    };
} // namespace hal
