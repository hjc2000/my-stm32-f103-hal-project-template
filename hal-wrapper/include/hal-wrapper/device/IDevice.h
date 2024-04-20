#pragma once

namespace hal
{
	class IDevice
	{
	private:
		IDevice(IDevice const &o) = delete;
		IDevice &operator=(IDevice const &o) = delete;

	protected:
		IDevice() = default;
	};
}