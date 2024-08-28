#include <base/container/StdMapValuesEnumerable.h>
#include <base/Initializer.h>
#include <bsp-interface/di/serial.h>
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

class Collection :
    public base::IReadOnlyDictionary<std::string, bsp::ISerial *>
{
private:
    std::map<std::string, bsp::ISerial *> _map;

    void Add(bsp::ISerial *serial)
    {
        _map[serial->Name()] = serial;
    }

public:
    Collection()
    {
        Add(&hal::Serial::Instance());
    }

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

    std::shared_ptr<base::IEnumerator<bsp::ISerial *>> GetEnumerator() override
    {
        return std::shared_ptr<base::IEnumerator<bsp::ISerial *>>{
            new base::StdMapValuesEnumerator<std::string, bsp::ISerial *>{
                &_map,
            },
        };
    }
};

base::IReadOnlyDictionary<std::string, bsp::ISerial *> &DI_SerialCollection()
{
    static Collection o;
    return o;
}
