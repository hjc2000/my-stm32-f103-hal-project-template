#include <AtkKey.h>
#include <base/container/Collection.h>
#include <base/Initializer.h>
#include <base/RentedPtrFactory.h>
#include <bsp-interface/di/key.h>
#include <bsp-interface/di/led.h>
#include <bsp-interface/key/KeyScanner.h>
#include <bsp/bsp.h>
#include <DigitalLed.h>
#include <Lcd.h>

using namespace bsp;

static base::Initializer _initializer{
    []()
    {
        DI_KeyCollection();
        DI_KeyScanner();
        DI_DigitalLedCollection();
    }};

#pragma region DI_KeyScanner

base::ICollection<std::string, bsp::IKey *> const &DI_KeyCollection()
{
    class Collection
    {
    public:
        Collection()
        {
            AddKey(&Key0::Instance());
            AddKey(&Key1::Instance());
        }

        base::Collection<std::string, bsp::IKey *> _collection;

        void AddKey(bsp::IKey *key)
        {
            _collection.Put(key->KeyName(), key);
        }
    };

    static Collection o;
    return o._collection;
}

bsp::IKeyScanner &DI_KeyScanner()
{
    static bsp::KeyScanner key_scanner{};
    return key_scanner;
}

#pragma endregion

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
