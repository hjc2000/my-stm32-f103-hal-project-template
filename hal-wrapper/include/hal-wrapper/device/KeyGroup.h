#pragma once
#include<hal-wrapper/device/Key.h>
#include<stdint.h>

namespace hal
{
	/// <summary>
	///		管理一组独立按键
	/// </summary>
	/// <typeparam name="KeyCount"></typeparam>
	template<uint16_t KeyCount>
	class KeyGroup
	{
	public:
		KeyGroup(Key **keys, uint16_t key_count) :
			_keys(keys)
		{

		}

	private:
		Key **_keys = nullptr;
		bool _handled_flag[KeyCount]{ false };

	public:

	};
}