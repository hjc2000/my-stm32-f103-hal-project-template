#pragma once

namespace bsp
{
	/// <summary>
	///		事件驱动的按钮。由外部事件驱动，设置标志位来表示按键被按下了。
	///		这里只提供读取标志的方法。
	/// </summary>
	class IEventDrivenKey
	{
	public:
		virtual bool IsPressed() = 0;
		virtual void ClearPressedFlag() = 0;
	};
}
