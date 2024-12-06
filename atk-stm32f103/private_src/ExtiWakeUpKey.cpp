#include "ExtiWakeUpKey.h"

using namespace bsp;

ExtiWakeUpKey::ExtiWakeUpKey()
{
    _pin = DI_GpioPinCollection().Get("PA0");
    _pin->OpenAsInputMode(bsp::IGpioPinPullMode::PullDown,
                          bsp::IGpioPinTriggerEdge::RisingEdge);

    _pin->RegisterInterruptCallback(
        [&]()
        {
            // 这是在中断函数中，禁止使用 Delayer 进行延时。
            DI_SysTick().Delay(std::chrono::milliseconds{20});
            _is_pressed = _pin->ReadPin();
        });
}
