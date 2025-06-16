#include "timed_waiter.hpp"

namespace sabre::esp32
{
    uint64_t TimedWaiter::_get_current_time() const
    {
        return esp_timer_get_time() / 1000;
    }

    void TimedWaiter::_sleep() const
    {
        vTaskDelay(_sleep_time / portTICK_PERIOD_MS);
    }

    TimedWaiter::TimedWaiter(sabre::TimedWaiterPred fn, uint64_t timeout_in_ms,
                             uint64_t sleep_time)
        : sabre::TimedWaiter(fn, timeout_in_ms, sleep_time)
    {
    }
} // namespace sabre::esp32