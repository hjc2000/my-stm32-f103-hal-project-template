#pragma once
#include <base/define.h>
#include <base/di/SingletonGetter.h>
#include <bsp-interface/di/interrupt.h>
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

        static_function void OnMspInitCallback(WWDG_HandleTypeDef *handle);
        static_function void OnEarlyWakeUpInterruptCallback(WWDG_HandleTypeDef *handle);

    public:
        WWDG_HandleTypeDef _handle;

        static_function WindowWatchDog &Instance()
        {
            class Getter :
                public base::SingletonGetter<WindowWatchDog>
            {
            public:
                std::unique_ptr<WindowWatchDog> Create() override
                {
                    return std::unique_ptr<WindowWatchDog>{new WindowWatchDog{}};
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

        WWDG_TypeDef *HardwareInstance();

        void Initialize(WindowWatchDogConfig &options);
        void Feed();
        void SetEarlyWakeupInterruptCallback(std::function<void()> func);
    };
} // namespace hal
