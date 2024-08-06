#include <AtkKey.h>
#include <DigitalLed.h>
#include <Lcd.h>
#include <base/Initializer.h>
#include <base/RentedPtrFactory.h>
#include <base/container/StdContainerEnumerable.h>
#include <base/container/StdMapValuesEnumerable.h>
#include <bsp-interface/di.h>
#include <bsp-interface/key/KeyScanner.h>
#include <bsp/bsp.h>
#include <hal-wrapper/peripheral/independent-watch-dog/IndependentWatchDog.h>

using namespace bsp;

static base::Initializer _initializer{
	[]()
	{
		DI_KeyCollection();
		DI_KeyScanner();
		DI_DigitalLedCollection();
	}};

#pragma region DI_KeyScanner
base::IReadOnlyCollection<int, bsp::IKey *> &DI_KeyCollection()
{
	class Collection
		: public base::IReadOnlyCollection<int, bsp::IKey *>
	{
	private:
		std::array<bsp::IKey *, static_cast<int>(KeyIndex::EnumEndFlag)> _array = {
			&Key0::Instance(),
			&Key1::Instance(),
		};

		base::StdContainerEnumerable<bsp::IKey *, std::array<bsp::IKey *,
															 static_cast<int>(KeyIndex::EnumEndFlag)>>
			_array_enumerable{
				base::RentedPtrFactory::Create(&_array),
			};

	public:
		int
		Count() const override
		{
			return static_cast<int>(_array.size());
		}

		bsp::IKey *Get(int key) const override
		{
			return _array[key];
		}

		std::shared_ptr<base::IEnumerator<bsp::IKey *>> GetEnumerator() override
		{
			return _array_enumerable.GetEnumerator();
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
	class Collection
		: public base::IReadOnlyCollection<std::string, bsp::IDigitalLed *>
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

#pragma region DI_IndependentWatchDog
bsp::IIndependentWatchDog &DI_IndependentWatchDog()
{
	return hal::IndependentWatchDog::Instance();
}
#pragma endregion
