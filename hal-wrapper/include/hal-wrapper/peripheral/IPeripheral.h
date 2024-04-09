#pragma once

namespace hal
{
	class IPeripheral
	{
	private:
		IPeripheral(IPeripheral const &another) = delete;
		IPeripheral &operator=(IPeripheral const &value) = delete;

	protected:
		IPeripheral() {}
	};
}