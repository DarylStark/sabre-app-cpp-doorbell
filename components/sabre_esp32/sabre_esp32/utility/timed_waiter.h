#ifndef SABRE_ESP32_TIMED_WAITER_H
#define SABRE_ESP32_TIMED_WAITER_H

#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <sabre/utility/timed_waiter.h>

namespace sabre::esp32
{
    class TimedWaiter : public sabre::TimedWaiter
    {
    protected:
        uint64_t _get_current_time() const;
        void _sleep() const;

    public:
        TimedWaiter(sabre::TimedWaiterPred fn, uint64_t timeout_in_ms,
                    uint64_t sleep_time = 0);
    };
    using TimedWaiterPtr = TimedWaiter *;
    using TimedWaiterSharedPtr = std::shared_ptr<TimedWaiter>;
} // namespace sabre::esp32

#endif // SABRE_ESP32_TIMED_WAITER_H