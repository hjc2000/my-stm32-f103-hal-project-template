#include <base/container/Dictionary.h>
#include <base/di/SingletonGetter.h>
#include <base/RentedPtrFactory.h>
#include <bsp-interface/di/interrupt.h>
#include <bsp-interface/di/led.h>
#include <bsp/bsp.h>
#include <DigitalLed.h>
#include <Lcd.h>

using namespace bsp;

#pragma region LED

base::IDictionary<std::string, bsp::IDigitalLed *> const &DI_DigitalLedCollection()
{
    class Initializer
    {
    private:
        Initializer() = default;

    public:
        base::Dictionary<std::string, bsp::IDigitalLed *> _collection{
            {"red_led", &RedDigitalLed::Instance()},
            {"green_led", &GreenDigitalLed::Instance()},
        };

        static_function Initializer &Instance()
        {
            class Getter :
                public base::SingletonGetter<Initializer>
            {
            public:
                std::unique_ptr<Initializer> Create() override
                {
                    return std::unique_ptr<Initializer>{new Initializer{}};
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
    };

    return Initializer::Instance()._collection;
}

bsp::IDigitalLed &DI_RedDigitalLed()
{
    return RedDigitalLed::Instance();
}

bsp::IDigitalLed &DI_GreenDigitalLed()
{
    return GreenDigitalLed::Instance();
}

#pragma endregion

#pragma region DI_Lcd

bsp::ILcd &DI_Lcd()
{
    return Lcd::Instance();
}

#pragma endregion
