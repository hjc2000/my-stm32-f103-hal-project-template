#include <base/container/Collection.h>
#include <base/SingletonGetter.h>
#include <bsp-interface/di/interrupt.h>
#include <bsp-interface/di/serial.h>
#include <hal-wrapper/peripheral/serial/Serial.h>

std::shared_ptr<bsp::ISerialOptions> DICreate_ISerialOptions()
{
    return std::shared_ptr<bsp::ISerialOptions>{new hal::SerialOptions{}};
}

bsp::ISerial &DI_Serial()
{
    return hal::Serial::Instance();
}

base::ICollection<std::string, bsp::ISerial *> const &DI_SerialCollection()
{
    class Initializer
    {
    private:
        Initializer()
        {
            Add(&hal::Serial::Instance());
        }

        void Add(bsp::ISerial *serial)
        {
            _collection.Put(serial->Name(), serial);
        }

    public:
        base::Collection<std::string, bsp::ISerial *> _collection;

        static Initializer &Instance()
        {
            class Getter : public base::SingletonGetter<Initializer>
            {
            public:
                std::unique_ptr<Initializer> Create() override
                {
                    return std::unique_ptr<Initializer>{new Initializer{}};
                }

                void Lock() override
                {
                    DI_InterruptSwitch().DisableGlobalInterrupt();
                }

                void Unlock() override
                {
                    DI_InterruptSwitch().EnableGlobalInterrupt();
                }
            };

            Getter g;
            return g.Instance();
        }
    };

    return Initializer::Instance()._collection;
}
