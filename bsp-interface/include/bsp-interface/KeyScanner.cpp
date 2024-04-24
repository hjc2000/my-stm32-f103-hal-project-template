#include"KeyScanner.h"

using namespace bsp;

void KeyScanner::ScanKeysNoDelay(std::vector<bool> &out)
{
	for (uint16_t i = 0; i < _keys.size(); i++)
	{
		out[i] = _keys[i]->KeyIsDown();
	}
}

KeyScanner::KeyScanner(std::vector<IKey *> keys) :
	_keys(keys),
	_last_scan_result(keys.size(), false),
	_current_scan_result(keys.size(), false),

	_key_down_events(keys.size(), false),
	_key_up_events(keys.size(), false),
	_key_pressed_events(keys.size(), false),

	_no_delay_scan_result1(keys.size(), false),
	_no_delay_scan_result2(keys.size(), false)
{

}

void KeyScanner::ScanKeys()
{
	ScanKeysNoDelay(_no_delay_scan_result1);
	Delay(std::chrono::milliseconds(10));
	ScanKeysNoDelay(_no_delay_scan_result2);
	for (uint16_t i = 0; i < _keys.size(); i++)
	{
		_current_scan_result[i] = _no_delay_scan_result1[i] && _no_delay_scan_result2[i];
	}

	// 更新事件状态
	for (uint16_t i = 0; i < _keys.size(); i++)
	{
		_key_down_events[i] = (!_last_scan_result[i]) && _current_scan_result[i];
		_key_up_events[i] = _last_scan_result[i] && (!_current_scan_result[i]);
	}

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
