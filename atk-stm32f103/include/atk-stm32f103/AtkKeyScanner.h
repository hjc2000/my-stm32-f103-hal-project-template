#pragma once
#include<bsp-interface/IKey.h>

namespace atk
{
	class AtkKeyScanner :public bsp::KeyScanner<3>
	{
		AtkKeyScanner() = default;

	public:
		void Delay(std::chrono::milliseconds num) override;
		bsp::IKey **KeyList() override;

		static AtkKeyScanner &Instance()
		{
			static AtkKeyScanner o;
			return o;
		}
	};
}