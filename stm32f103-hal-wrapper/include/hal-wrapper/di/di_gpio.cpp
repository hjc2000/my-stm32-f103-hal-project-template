#include <bsp-interface/di.h>
#include <gpio/GpioPinOptions.h>
#include <gpio/GpioPinPA0.h>
#include <gpio/GpioPinPA10.h>
#include <gpio/GpioPinPA9.h>
#include <gpio/GpioPinPB0.h>
#include <gpio/GpioPinPB5.h>
#include <gpio/GpioPinPD4.h>
#include <gpio/GpioPinPD5.h>
#include <gpio/GpioPinPE3.h>
#include <gpio/GpioPinPE4.h>
#include <gpio/GpioPinPE5.h>
#include <gpio/GpioPinPG0.h>
#include <gpio/GpioPinPG12.h>

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
			AddPin(bsp::GpioPinPA0::Instance());
			AddPin(bsp::GpioPinPA9::Instance());
			AddPin(bsp::GpioPinPA10::Instance());
			AddPin(bsp::GpioPinPB0::Instance());
			AddPin(bsp::GpioPinPB5::Instance());
			AddPin(bsp::GpioPinPD4::Instance());
			AddPin(bsp::GpioPinPD5::Instance());
			AddPin(bsp::GpioPinPE3::Instance());
			AddPin(bsp::GpioPinPE4::Instance());
			AddPin(bsp::GpioPinPE5::Instance());
			AddPin(bsp::GpioPinPG0::Instance());
			AddPin(bsp::GpioPinPG12::Instance());
		}

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
	};

	static Collection o;
	return o;
}
