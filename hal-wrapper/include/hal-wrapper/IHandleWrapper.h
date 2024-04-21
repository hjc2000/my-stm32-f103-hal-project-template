#pragma once

namespace hal
{
	template<typename HandleType>
	class IHandleWrapper
	{
	public:
		/// <summary>
		///		返回 XXX_HandleTypeDef 的指针。
		/// </summary>
		/// <returns></returns>
		virtual HandleType *Handle() = 0;
	};
}