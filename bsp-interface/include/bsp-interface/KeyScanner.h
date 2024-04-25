#pragma once
#include<boost/dynamic_bitset.hpp>
#include<bsp-interface/IKey.h>
#include<bsp-interface/IKeyScanner.h>
#include<vector>

namespace bsp
{
	/// <summary>
	///		按键扫描器
	/// </summary>
	/// <typeparam name="KeyCount"></typeparam>
	class KeyScanner :public bsp::IKeyScanner
	{
	private:
		std::vector<IKey *> _keys;
		boost::dynamic_bitset<> _last_scan_result;
		boost::dynamic_bitset<> _current_scan_result;

		boost::dynamic_bitset<> _key_down_events;
		boost::dynamic_bitset<> _key_up_events;
		boost::dynamic_bitset<> _key_pressed_events;

		boost::dynamic_bitset<> _no_delay_scan_result1;
		boost::dynamic_bitset<> _no_delay_scan_result2;

		void ScanKeysNoDelay(boost::dynamic_bitset<> &out);

	public:
		KeyScanner(std::vector<IKey *> keys);

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
		void ScanKeys() override;

		bool HasKeyDownEvent(uint16_t key_index) override;
		bool HasKeyUpEvent(uint16_t key_index) override;
		bool HasKeyPressedEvent(uint16_t key_index) override;

		void ClearAllEvent(uint16_t key_index) override;
		void ClearKeyDownEvent(uint16_t key_index) override;
		void ClearKeyUpEvent(uint16_t key_index) override;
		void ClearKeyPressedEvent(uint16_t key_index) override;
	};
}
