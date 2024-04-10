#pragma once
#include<hal-wrapper/container/List.h>
#include<hal-wrapper/device/Key.h>

namespace hal
{
	template<uint16_t KeyCount>
	class KeyScanner
	{
	public:
		List<Key *, KeyCount> _key_list;
	};
}