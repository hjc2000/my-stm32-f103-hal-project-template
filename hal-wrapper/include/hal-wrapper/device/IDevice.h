#pragma once

namespace hal
{
	class IDevice
	{
	public:
		virtual void Initialize() = 0;
		virtual void Deinitialize() = 0;
	};
}