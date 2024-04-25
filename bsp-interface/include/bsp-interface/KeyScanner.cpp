#include"KeyScanner.h"

using namespace bsp;

void KeyScanner::ScanKeysNoDelay(boost::dynamic_bitset<> &out)
{
	for (uint16_t i = 0; i < _keys.size(); i++)
	{
		out[i] = _keys[i]->KeyIsDown();
	}
}

KeyScanner::KeyScanner(std::vector<IKey *> const &keys, bsp::IDelayer &delayer) :
	_keys(keys),
	_delayer(delayer),

	_last_scan_result(keys.size()),
	_current_scan_result(keys.size()),

	_key_down_events(keys.size()),
	_key_up_events(keys.size()),
	_key_pressed_events(keys.size()),

	_no_delay_scan_result1(keys.size()),
	_no_delay_scan_result2(keys.size())
{

}

void KeyScanner::ScanKeys()
{
	ScanKeysNoDelay(_no_delay_scan_result1);
	_delayer.Delay(std::chrono::milliseconds(10));
	ScanKeysNoDelay(_no_delay_scan_result2);
	_current_scan_result = _no_delay_scan_result1 & _no_delay_scan_result2;

	// 更新事件状态
	_key_down_events = (~_last_scan_result) & _current_scan_result;
	_key_up_events = _last_scan_result & (~_current_scan_result);
	_key_pressed_events = _current_scan_result;
	_last_scan_result = _current_scan_result;
}

bool KeyScanner::HasKeyDownEvent(uint16_t key_index)
{
	if (key_index >= _keys.size())
	{
		return false;
	}

	return _key_down_events[key_index];
}

bool KeyScanner::HasKeyUpEvent(uint16_t key_index)
{
	if (key_index >= _keys.size())
	{
		return false;
	}

	return _key_up_events[key_index];
}

bool KeyScanner::HasKeyPressedEvent(uint16_t key_index)
{
	if (key_index >= _keys.size())
	{
		return false;
	}

	return _key_pressed_events[key_index];
}

void KeyScanner::ClearAllEvent(uint16_t key_index)
{
	_key_down_events[key_index] = false;
	_key_up_events[key_index] = false;
	_key_pressed_events[key_index] = false;
}

void KeyScanner::ClearKeyDownEvent(uint16_t key_index)
{
	_key_down_events[key_index] = false;
}

void KeyScanner::ClearKeyUpEvent(uint16_t key_index)
{
	_key_up_events[key_index] = false;
}

void KeyScanner::ClearKeyPressedEvent(uint16_t key_index)
{
	_key_pressed_events[key_index] = false;
}
