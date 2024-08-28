#include "Dma1Channel5.h"
#include "DmaOptions.h"
#include <base/container/StdMapValuesEnumerator.h>
#include <base/Initializer.h>
#include <bsp-interface/di/dma.h>
#include <map>

base::Initializer _initializer{
    []()
    {
        DI_DmaChannel();
    }};

std::shared_ptr<bsp::IDmaOptions> DICreate_DmaOptions()
{
    return std::shared_ptr<bsp::IDmaOptions>{new bsp::DmaOptions{}};
}

class Collection :
    public base::IReadOnlyDictionary<std::string, bsp::IDmaChannel *>
{
private:
    std::map<std::string, bsp::IDmaChannel *> _map;

    void Add(bsp::IDmaChannel *o)
    {
        _map[o->Name()] = o;
    }

public:
    Collection()
    {
        Add(&bsp::Dma1Channel5::Instance());
    }

    virtual int Count() const override
    {
        return _map.size();
    }

    virtual bsp::IDmaChannel *Get(std::string key) const override
    {
        auto it = _map.find(key);
        if (it == _map.end())
        {
            throw std::runtime_error{"找不到此 DMA"};
        }

        return it->second;
    }

    std::shared_ptr<base::IEnumerator<bsp::IDmaChannel *>> GetEnumerator() override
    {
        return std::shared_ptr<base::IEnumerator<bsp::IDmaChannel *>>{
            new base::StdMapValuesEnumerator<std::string, bsp::IDmaChannel *>{
                &_map,
            },
        };
    }
};

base::IReadOnlyDictionary<std::string, bsp::IDmaChannel *> &DI_DmaChannel()
{
    static Collection o;
    return o;
}
