#pragma once
#include<bsp-interface/IDelayer.h>
#include<chrono>
#include<stdint.h>

namespace hal
{
	/// <summary>
	///		延时器。内部默认使用 Systic 类进行延时。
	/// </summary>
	class Delayer :public bsp::IDelayer
	{
	private:
		Delayer() = default;
		Delayer(Delayer const &o) = delete;
		Delayer &operator=(Delayer const &o) = delete;

	public:
		#pragma region 单例
		static Delayer &Instance()
		{
			static Delayer delayer{};
			if (_global_delayer != nullptr)
			{
				return *_global_delayer;
			}

			return delayer;
		}

		/// <summary>
		///		设置后 Instance 方法将会返回此对象，否则会返回 Delayer
		///		的默认实现。
		/// </summary>
		static Delayer *_global_delayer;
		#pragma endregion

		virtual void Delay(std::chrono::microseconds microseconds) override;
		virtual void Delay(std::chrono::milliseconds milliseconds) override;
		virtual void Delay(std::chrono::seconds seconds) override;
	};
}