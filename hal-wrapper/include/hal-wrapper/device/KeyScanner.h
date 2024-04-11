#pragma once
#include<bitset>
#include<hal-wrapper/device/Key.h>

namespace hal
{
	template<uint16_t KeyCount>
	class KeyScanner
	{
	public:
		KeyScanner(Key *keys)
		{
			_keys = nullptr;
		}

	private:
		Key *_keys = nullptr;

		std::bitset<KeyCount> ScanKeysNoDelay()
		{
			std::bitset<KeyCount> key_down_flags;
			for (uint16_t i = 0; i < KeyCount; i++)
			{
				if (_keys[i].KeyIsDown())
				{
					key_down_flags[i] = 1;
				}
			}
		}

	public:
		std::bitset<KeyCount> ScanKeys()
		{
			std::bitset<KeyCount> first_scan_result = ScanKeysNoDelay();

		}
	};
}