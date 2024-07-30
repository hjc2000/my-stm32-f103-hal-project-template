#include <base/Initializer.h>
#include <bsp-interface/di.h>
#include <hal-wrapper/interrupt/Interrupt.h>

bsp::IInterruptSwitch &DI_InterruptSwitch()
{
	class InterruptSwitch : public bsp::IInterruptSwitch
	{
	public:
		void DisableInterrupt(uint32_t irq) noexcept override
		{
			hal::Interrupt::DisableIRQ(static_cast<IRQn_Type>(irq));
		}

		void EnableInterrupt(uint32_t irq) noexcept override
		{
			hal::Interrupt::EnableIRQ(static_cast<IRQn_Type>(irq));
		}

		/// @brief 禁止全局中断
		virtual void DisableGlobalInterrupt() noexcept
		{
			__disable_irq();
		}

		/// @brief 启用全局中断
		virtual void EnableGlobalInterrupt() noexcept
		{
			__enable_irq();
		}
	};

	static InterruptSwitch o;
	return o;
}
