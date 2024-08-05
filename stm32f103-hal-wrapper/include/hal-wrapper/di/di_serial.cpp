#include <base/Initializer.h>
#include <bsp-interface/di.h>
#include <hal-wrapper/peripheral/serial/Serial.h>

static base::Initializer _initializer{
	[]()
	{
		DI_SerialCollection();
	}};

std::shared_ptr<bsp::ISerialOptions> DICreate_ISerialOptions()
{
	return std::shared_ptr<bsp::ISerialOptions>{new hal::SerialOptions{}};
}

bsp::ISerial &DI_Serial()
{
	return hal::Serial::Instance();
}

base::IReadOnlyCollection<std::string, bsp::ISerial *> &DI_SerialCollection()
{
	class Collection
		: public base::IReadOnlyCollection<std::string, bsp::ISerial *>
	{
	private:
		std::map<std::string, bsp::ISerial *> _map{
			{"serial", &hal::Serial::Instance()},
		};

	public:
		int Count() const override
		{
			return _map.size();
		}

		bsp::ISerial *Get(std::string key) const override
		{
			auto it = _map.find(key);
			if (it == _map.end())
			{
				return nullptr;
			}

			return it->second;
		}
	};

	static Collection o;
	return o;
}
