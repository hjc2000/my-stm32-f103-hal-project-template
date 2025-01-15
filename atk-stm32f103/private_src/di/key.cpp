#include <AtkKey.h>
#include <base/container/Dictionary.h>
#include <bsp-interface/di/interrupt.h>
#include <bsp-interface/di/key.h>
#include <bsp-interface/TaskSingletonGetter.h>

base::IDictionary<std::string, bsp::IKey *> const &DI_KeyCollection()
{
    class Initializer
    {
    private:
        Initializer()
        {
            AddKey(&bsp::Key0::Instance());
            AddKey(&bsp::Key1::Instance());
        }

    public:
        base::Dictionary<std::string, bsp::IKey *> _collection;

        void AddKey(bsp::IKey *key)
        {
            _collection.Add(key->KeyName(), key);
        }

        static_function Initializer &Instance()
        {
            class Getter :
                public bsp::TaskSingletonGetter<Initializer>
            {
            public:
                std::unique_ptr<Initializer> Create() override
                {
                    return std::unique_ptr<Initializer>{new Initializer{}};
                }
            };

            Getter g;
            return g.Instance();
        }
    };

    return Initializer::Instance()._collection;
}
