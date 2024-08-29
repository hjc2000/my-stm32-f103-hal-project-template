#include <base/container/Collection.h>
#include <base/Initializer.h>
#include <base/RentedPtrFactory.h>
#include <bsp-interface/di/led.h>
#include <bsp/bsp.h>
#include <DigitalLed.h>
#include <Lcd.h>

using namespace bsp;

static base::Initializer _initializer{
    []()
    {
        DI_DigitalLedCollection();
    }};

#pragma region LED

base::ICollection<std::string, bsp::IDigitalLed *> const &DI_DigitalLedCollection()
{
    class Collection
    {
    public:
        base::Collection<std::string, bsp::IDigitalLed *> _collection{
            {"red_led", &RedDigitalLed::Instance()},
            {"green_led", &GreenDigitalLed::Instance()},
        };
    };

    static Collection o;
    return o._collection;
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
