#pragma once
#include<bitset>
#include<hal-wrapper/Delayer.h>
#include<hal-wrapper/device/Key.h>

namespace hal
{
	template<uint16_t KeyCount>
	class KeyScanner
	{
	private:
		Key **_keys = nullptr;
		std::bitset<KeyCount> _last_scan_result;
		std::bitset<KeyCount> _key_down_events;
		std::bitset<KeyCount> _key_up_events;
		std::bitset<KeyCount> _key_pressed_events;

		std::bitset<KeyCount> ScanKeysNoDelay()
		{
			std::bitset<KeyCount> key_down_flags;
			for (uint16_t i = 0; i < KeyCount; i++)
			{
				if (_keys[i]->KeyIsDown())
				{
					key_down_flags[i] = 1;
				}
			}

			return key_down_flags;
		}

	public:
		/// <summary>
		///		将按键对象的指针放到数组里，将数组头指针传进来。
		/// </summary>
		/// <param name="keys"></param>
		KeyScanner(Key **keys)
		{
			_keys = keys;
		}

		/// <summary>
		///		执行键盘扫描，更新内部状态。此函数应该被不断调用。
		/// </summary>
		void ScanKeys()
		{
			std::bitset<KeyCount> first_scan_result = ScanKeysNoDelay();
			// 延时消抖
			Delayer::Instance().Delay(std::chrono::milliseconds(10));
			std::bitset<KeyCount> scan_result = first_scan_result & ScanKeysNoDelay();

			// 更新事件状态
			_key_down_events = (~_last_scan_result) & scan_result;
			_key_up_events = _last_scan_result & (~scan_result);
			_key_pressed_events = scan_result;
			_last_scan_result = scan_result;
		}

		/// <summary>
		///		获取按键按下事件。
		/// </summary>
		/// <returns></returns>
		std::bitset<KeyCount> GetKeyDownEvents() const
		{
			return _key_down_events;
		}

		/// <summary>
		///		获取按键释放事件。
		/// </summary>
		/// <returns></returns>
		std::bitset<KeyCount> GetKeyUpEvents() const
		{
			return _key_up_events;
		}

		/// <summary>
		///		获取当前处于按下状态的按键。
		/// </summary>
		/// <returns></returns>
		std::bitset<KeyCount> GetKeyPressedEvents() const
		{
			return _key_pressed_events;
		}
	};
}