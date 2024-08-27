#include <AtkKey.h>
#include <base/container/StdContainerEnumerable.h>
#include <base/container/StdMapValuesEnumerable.h>
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

base::IReadOnlyCollection<std::string, bsp::IKey *> &DI_KeyCollection()
{
    class Collection : public base::IReadOnlyCollection<std::string, bsp::IKey *>
    {
    private:
        std::map<std::string, bsp::IKey *> _map;

        void AddKey(bsp::IKey *key)
        {
            _map[key->KeyName()] = key;
        }

    public:
        Collection()
        {
            AddKey(&Key0::Instance());
            AddKey(&Key1::Instance());
        }

        int Count() const override
        {
            return static_cast<int>(_map.size());
        }

        bsp::IKey *Get(std::string key) const override
        {
            auto map = const_cast<Collection *>(this)->_map;
            auto it = map.find(key);
            if (it == map.end())
            {
                throw std::runtime_error{"找不到此按键"};
            }

            return it->second;
        }

        std::shared_ptr<base::IEnumerator<bsp::IKey *>> GetEnumerator() override
        {
            return std::shared_ptr<base::IEnumerator<bsp::IKey *>>{
                new base::StdMapValuesEnumerator<std::string, bsp::IKey *>{&_map},
            };
        }
    };

    static Collection o;
    return o;
}

bsp::IKeyScanner &DI_KeyScanner()
{
    static bsp::KeyScanner key_scanner{};
    return key_scanner;
}

#pragma endregion

#pragma region LED

base::IReadOnlyCollection<std::string, bsp::IDigitalLed *> &DI_DigitalLedCollection()
{
    class Collection : public base::IReadOnlyCollection<std::string, bsp::IDigitalLed *>
    {
    private:
        std::map<std::string, bsp::IDigitalLed *> _led_map{
            {"red_led", &RedDigitalLed::Instance()},
            {"green_led", &GreenDigitalLed::Instance()},
        };

    public:
        int Count() const override
        {
            return static_cast<int>(_led_map.size());
        }

        bsp::IDigitalLed *Get(std::string key) const override
        {
            auto it = _led_map.find(key);
            if (it == _led_map.end())
            {
                return nullptr;
            }

            return it->second;
        }

        std::shared_ptr<base::IEnumerator<bsp::IDigitalLed *>> GetEnumerator() override
        {
            return std::shared_ptr<base::IEnumerator<bsp::IDigitalLed *>>{
                new base::StdMapValuesEnumerator<std::string, bsp::IDigitalLed *>{
                    &_led_map,
                },
            };
        }
    };

    static Collection o;
    return o;
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
