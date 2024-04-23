#pragma once
#include<bitset>
#include<hal-wrapper/clock/Delayer.h>

namespace hal
{
	/// <summary>
	///		独立按键。
	///		所谓独立按键就是一个按键占用一个 GPIO 引脚。
	/// </summary>
	class IKey
	{
	public:
		/// <summary>
		///		按键处于被按下的状态。
		///		此函数内部不会进行按键消抖，抖动会引起此函数返回值的变化。
		/// </summary>
		/// <returns>按键处于被按下的状态则返回 true，按键不处于被按下的状态则返回 false。</returns>
		virtual bool KeyIsDown() = 0;

		bool KeyIsUp()
		{
			return !KeyIsDown();
		}

		/// <summary>
		///		经过软件消抖，确定按键确实是处于被按下的状态。
		/// </summary>
		/// <returns>按键处于被按下的状态则返回 true，按键不处于被按下的状态则返回 false。</returns>
		virtual bool KeyIsReallyDown();

		/// <summary>
		///		经过如按键消抖，确定按键确实是处于起来的状态。
		/// </summary>
		/// <returns></returns>
		virtual bool KeyIsReallyUp();
	};

	/// <summary>
	///		按键扫描器
	/// </summary>
	/// <typeparam name="KeyCount"></typeparam>
	template<uint16_t KeyCount>
	class KeyScanner
	{
	private:
		IKey **_keys = nullptr;
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
		KeyScanner(IKey **keys)
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
