#pragma once

namespace hal
{
	class IDevice
	{
	private:
		IDevice(IDevice const &another) = delete;

	protected:
		IDevice() {}

	public:
		virtual void Initialize() = 0;
		virtual void Deinitialize() = 0;
	};
}