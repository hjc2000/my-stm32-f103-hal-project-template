#pragma once
#include<bsp-interface/IKey.h>

namespace bsp
{
	/// <summary>
	///		按键扫描器
	/// </summary>
	/// <typeparam name="KeyCount"></typeparam>
	template<uint16_t KeyCount>
	class KeyScanner
	{
	private:
		std::bitset<KeyCount> _last_scan_result;
		std::bitset<KeyCount> _key_down_events;
		std::bitset<KeyCount> _key_up_events;
		std::bitset<KeyCount> _key_pressed_events;

		std::bitset<KeyCount> ScanKeysNoDelay()
		{
			std::bitset<KeyCount> key_down_flags;
			for (uint16_t i = 0; i < KeyCount; i++)
			{
				if (KeyList()[i]->KeyIsDown())
				{
					key_down_flags[i] = 1;
				}
			}

			return key_down_flags;
		}

	public:
		virtual IKey **KeyList() = 0;

		/// <summary>
		///		按键扫描需要延时消抖。
		///		- 如果被本扫描器扫描的所有按钮都有滤波电路，不需要消抖，
		///		  则可将本函数实现为什么都不做，直接返回。
		/// </summary>
		/// <param name="num"></param>
		virtual void Delay(std::chrono::milliseconds num) = 0;

		/// <summary>
		///		执行键盘扫描，更新内部状态。此函数应该被不断调用。
		/// </summary>
		void ScanKeys()
		{
			std::bitset<KeyCount> first_scan_result = ScanKeysNoDelay();

			// 延时消抖
			Delay(std::chrono::milliseconds(10));
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
		///		获取当前处于按下状态的按键。只要按键一直被按着，就会一直触发。
		/// </summary>
		/// <returns></returns>
		std::bitset<KeyCount> GetKeyPressedEvents() const
		{
			return _key_pressed_events;
		}
	};
}
