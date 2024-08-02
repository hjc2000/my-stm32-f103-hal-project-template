#include <AtkKey.h>
#include <DigitalLed.h>
#include <Lcd.h>
#include <base/Initializer.h>
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

	public:
		int Count() const override
		{
			return static_cast<int>(_array.size());
		}

		bsp::IKey *Get(int key) const override
		{
			return _array[key];
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

#pragma region DI_DigitalLedCollection
base::IReadOnlyCollection<int, bsp::IDigitalLed *> &DI_DigitalLedCollection()
{
	class Collection
		: public base::IReadOnlyCollection<int, bsp::IDigitalLed *>
	{
	private:
		std::array<bsp::IDigitalLed *, 2> _array = {
			&RedDigitalLed::Instance(),
			&GreenDigitalLed::Instance(),
		};

	public:
		int Count() const override
		{
			return static_cast<int>(_array.size());
		}

		bsp::IDigitalLed *Get(int key) const override
		{
			return _array[key];
		}
	};

	static Collection o;
	return o;
}
#pragma endregion

#pragma region 具体颜色的 LED
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
