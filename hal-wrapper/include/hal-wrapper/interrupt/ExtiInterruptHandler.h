#pragma once

namespace hal
{
	class ExtiInterruptHandler
	{
		ExtiInterruptHandler() = default;

	public:
		static ExtiInterruptHandler &Instance()
		{
			static ExtiInterruptHandler instance;
			if (_default_handler != nullptr)
			{
				return *_default_handler;
			}

			return instance;
		}

		static ExtiInterruptHandler *_default_handler;

		virtual void HandleExti0Irq() {}
		virtual void HandleExti1Irq() {}
		virtual void HandleExti2Irq() {}
		virtual void HandleExti3Irq() {}
		virtual void HandleExti4Irq() {}
	};
}