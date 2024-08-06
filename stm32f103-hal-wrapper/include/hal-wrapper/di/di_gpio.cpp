#include <base/Initializer.h>
#include <base/container/StdMapValuesEnumerable.h>
#include <bsp-interface/di.h>
#include <gpio/GpioPinOptions.h>
#include <gpio/pins.h>

static base::Initializer _initializer{
	[]()
	{
		DI_GpioPinCollection();
	}};

std::shared_ptr<bsp::IGpioPinOptions> DICreate_GpioPinOptions()
{
	return std::shared_ptr<bsp::IGpioPinOptions>{new bsp::GpioPinOptions{}};
}

base::IReadOnlyCollection<std::string, bsp::IGpioPin *> &DI_GpioPinCollection()
{
	class Collection
		: public base::IReadOnlyCollection<std::string, bsp::IGpioPin *>
	{
	private:
		std::map<std::string, bsp::IGpioPin *> _pin_map{};

		void AddPin(bsp::IGpioPin &pin)
		{
			_pin_map[pin.PinName()] = &pin;
		}

	public:
		Collection()
		{
#pragma region PA
			AddPin(bsp::GpioPinPA0::Instance());
			AddPin(bsp::GpioPinPA9::Instance());
			AddPin(bsp::GpioPinPA10::Instance());
#pragma endregion

#pragma region PB
			AddPin(bsp::GpioPinPB0::Instance());
			AddPin(bsp::GpioPinPB5::Instance());
#pragma endregion

#pragma region PD
			AddPin(bsp::GpioPinPD0::Instance());
			AddPin(bsp::GpioPinPD1::Instance());
			AddPin(bsp::GpioPinPD4::Instance());
			AddPin(bsp::GpioPinPD5::Instance());
			AddPin(bsp::GpioPinPD8::Instance());
			AddPin(bsp::GpioPinPD9::Instance());
			AddPin(bsp::GpioPinPD10::Instance());
			AddPin(bsp::GpioPinPD11::Instance());
			AddPin(bsp::GpioPinPD14::Instance());
			AddPin(bsp::GpioPinPD15::Instance());
#pragma endregion

#pragma region PE
			AddPin(bsp::GpioPinPE3::Instance());
			AddPin(bsp::GpioPinPE4::Instance());
			AddPin(bsp::GpioPinPE5::Instance());
			AddPin(bsp::GpioPinPE7::Instance());
			AddPin(bsp::GpioPinPE8::Instance());
			AddPin(bsp::GpioPinPE9::Instance());
			AddPin(bsp::GpioPinPE10::Instance());
			AddPin(bsp::GpioPinPE11::Instance());
			AddPin(bsp::GpioPinPE12::Instance());
			AddPin(bsp::GpioPinPE13::Instance());
			AddPin(bsp::GpioPinPE14::Instance());
			AddPin(bsp::GpioPinPE15::Instance());
#pragma endregion

#pragma region PG
			AddPin(bsp::GpioPinPG0::Instance());
			AddPin(bsp::GpioPinPG12::Instance());
#pragma endregion
		}

#pragma region IReadOnlyCollection
		int Count() const override
		{
			return _pin_map.size();
		}

		bsp::IGpioPin *Get(std::string key) const override
		{
			auto it = _pin_map.find(key);
			if (it == _pin_map.end())
			{
				return nullptr;
			}

			return it->second;
		}

		std::shared_ptr<base::IEnumerator<bsp::IGpioPin *>> GetEnumerator() override
		{
			return std::shared_ptr<base::IEnumerator<bsp::IGpioPin *>>{
				new base::StdMapValuesEnumerator<std::string, bsp::IGpioPin *>{
					&_pin_map,
				},
			};
		}
#pragma endregion
	};

	static Collection o;
	return o;
}
