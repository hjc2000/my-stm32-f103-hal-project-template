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
		std::map<std::string, bsp::IGpioPin *> _pin_map{
			{bsp::GpioPinPA0::Instance().PinName(), &bsp::GpioPinPA0::Instance()},
			{bsp::GpioPinPA9::Instance().PinName(), &bsp::GpioPinPA9::Instance()},
			{bsp::GpioPinPA10::Instance().PinName(), &bsp::GpioPinPA10::Instance()},
			{bsp::GpioPinPB0::Instance().PinName(), &bsp::GpioPinPB0::Instance()},
			{bsp::GpioPinPB5::Instance().PinName(), &bsp::GpioPinPB5::Instance()},
			{bsp::GpioPinPD4::Instance().PinName(), &bsp::GpioPinPD4::Instance()},
			{bsp::GpioPinPD5::Instance().PinName(), &bsp::GpioPinPD5::Instance()},
			{bsp::GpioPinPE3::Instance().PinName(), &bsp::GpioPinPE3::Instance()},
			{bsp::GpioPinPE4::Instance().PinName(), &bsp::GpioPinPE4::Instance()},
			{bsp::GpioPinPE5::Instance().PinName(), &bsp::GpioPinPE5::Instance()},
			{bsp::GpioPinPG0::Instance().PinName(), &bsp::GpioPinPG0::Instance()},
			{bsp::GpioPinPG12::Instance().PinName(), &bsp::GpioPinPG12::Instance()},
		};

	public:
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
