#include "Dma1Channel5.h"
#include "DmaOptions.h"
#include <base/container/Collection.h>
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

class Collection
{
public:
    Collection()
    {
        Add(&bsp::Dma1Channel5::Instance());
    }

    base::Collection<std::string, bsp::IDmaChannel *> _collection;

    void Add(bsp::IDmaChannel *o)
    {
        _collection.Put(o->Name(), o);
    }
};

base::ICollection<std::string, bsp::IDmaChannel *> const &DI_DmaChannel()
{
    static Collection o;
    return o._collection;
}
