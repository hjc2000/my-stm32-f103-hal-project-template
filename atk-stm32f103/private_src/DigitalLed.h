#pragma once
#include <base/di/SingletonGetter.h>
#include <bsp-interface/di/gpio.h>
#include <bsp-interface/di/interrupt.h>
#include <bsp-interface/IDigitalLed.h>

namespace bsp
{
    /// @brief 红色 LED
    class RedDigitalLed : public bsp::IDigitalLed
    {
    private:
        RedDigitalLed();

        bsp::IGpioPin *_pin = nullptr;

    public:
        static RedDigitalLed &Instance()
        {
            class Getter : public base::SingletonGetter<RedDigitalLed>
            {
            public:
                std::unique_ptr<RedDigitalLed> Create() override
                {
                    return std::unique_ptr<RedDigitalLed>{new RedDigitalLed{}};
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

        void TurnOn() override;
        void TurnOff() override;
        void Toggle() override;
    };

    /// @brief 绿色 LED
    class GreenDigitalLed : public bsp::IDigitalLed
    {
    private:
        GreenDigitalLed();

        bsp::IGpioPin *_pin = nullptr;

    public:
        static GreenDigitalLed &Instance()
        {
            class Getter : public base::SingletonGetter<GreenDigitalLed>
            {
            public:
                std::unique_ptr<GreenDigitalLed> Create() override
                {
                    return std::unique_ptr<GreenDigitalLed>{new GreenDigitalLed{}};
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

        void TurnOn() override;
        void TurnOff() override;
        void Toggle() override;
    };
} // namespace bsp
