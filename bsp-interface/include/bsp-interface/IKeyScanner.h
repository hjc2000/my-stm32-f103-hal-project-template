#pragma once
#include<bsp-interface/IKey.h>
#include<cstdint>

namespace bsp
{
	class IKeyScanner
	{
	public:
		/// <summary>
		///		此函数需要被循环调用，这样才能扫描到按键事件。
		/// </summary>
		virtual void ScanKeys() = 0;

		virtual bool HasKeyDownEvent(uint16_t key_index) = 0;
		virtual bool HasKeyUpEvent(uint16_t key_index) = 0;
		virtual bool HasKeyPressedEvent(uint16_t key_index) = 0;

		virtual void ClearAllEvent(uint16_t key_index) = 0;
		virtual void ClearKeyDownEvent(uint16_t key_index) = 0;
		virtual void ClearKeyUpEvent(uint16_t key_index) = 0;
		virtual void ClearKeyPressedEvent(uint16_t key_index) = 0;
	};
}
