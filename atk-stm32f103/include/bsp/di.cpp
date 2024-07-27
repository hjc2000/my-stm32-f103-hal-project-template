#include <AtkKey.h>
#include <base/Initializer.h>
#include <bsp-interface/di.h>
#include <bsp-interface/key/KeyScanner.h>

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

	static base::ArrayCollection<2, bsp::IKey *> keys{
		std::array<bsp::IKey *, 2>{
			static_cast<bsp::IKey *>(&Key0::Instance()),
			static_cast<bsp::IKey *>(&Key1::Instance()),
		},
	};

	return keys;
}

bsp::IKeyScanner &DI_KeyScanner()
{
	static bsp::KeyScanner key_scanner{DI_KeyCollection()};
	return key_scanner;
}
#pragma endregion