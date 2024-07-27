#include <AtkKey.h>
#include <base/Initializer.h>
#include <bsp-interface/di.h>
#include <bsp-interface/key/KeyScanner.h>
#include <bsp/bsp.h>

using namespace bsp;

static base::Initializer _initializer{
	[]()
	{
		DI_KeyCollection();
		DI_KeyScanner();
	}};

#pragma region DI_KeyScanner
base::IReadOnlyCollection<int, bsp::IKey *> &DI_KeyCollection()
{
	class ArrayCollection
		: public base::IReadOnlyCollection<int, bsp::IKey *>
	{
	private:
		std::array<bsp::IKey *, static_cast<int>(KeyIndex::EnumEndFlag)> _array = {
			&Key0::Instance(),
			&Key1::Instance(),
		};

	public:
		int Count() const override
		{
			return static_cast<int>(_array.size());
		}

		bsp::IKey *Get(int key) const override
		{
			return _array[key];
		}
	};

	static ArrayCollection o;
	return o;
}

bsp::IKeyScanner &DI_KeyScanner()
{
	static bsp::KeyScanner key_scanner{DI_KeyCollection()};
	return key_scanner;
}
#pragma endregion