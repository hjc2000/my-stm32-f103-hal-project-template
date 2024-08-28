#include <base/container/Collection.h>
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

class Collection
{
public:
    Collection()
    {
        Add(&hal::Serial::Instance());
    }

    base::Collection<std::string, bsp::ISerial *> _collection;

    void Add(bsp::ISerial *serial)
    {
        _collection.Put(serial->Name(), serial);
    }
};

base::ICollection<std::string, bsp::ISerial *> const &DI_SerialCollection()
{
    static Collection o;
    return o._collection;
}
