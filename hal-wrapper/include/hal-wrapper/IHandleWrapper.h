#pragma once

namespace hal
{
	template<typename HandleType>
	class IHandleWrapper
	{
	private:
		IHandleWrapper(IHandleWrapper const &o) = delete;
		IHandleWrapper &operator=(IHandleWrapper const &o) = delete;

	protected:
		IHandleWrapper() = default;

	public:
		/// <summary>
		///		返回 XXX_HandleTypeDef 的指针。
		/// </summary>
		/// <returns></returns>
		virtual HandleType *Handle() = 0;
	};
}