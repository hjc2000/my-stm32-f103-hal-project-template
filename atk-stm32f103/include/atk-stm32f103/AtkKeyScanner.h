#pragma once
#include<bsp-interface/IKey.h>
#include<bsp-interface/KeyScanner.h>

namespace atk
{
	class AtkKeyScanner :public bsp::KeyScanner
	{
	public:
		AtkKeyScanner();

		static AtkKeyScanner &Instance()
		{
			static AtkKeyScanner o;
			return o;
		}
	};

	void TestKeyScanner();
}
