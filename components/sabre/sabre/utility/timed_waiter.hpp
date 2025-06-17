#ifndef SABRE_TIMED_WAITER_H
#define SABRE_TIMED_WAITER_H

#include <cstdint>
#include <functional>
#include <memory>

namespace sabre
{
    using TimedWaiterPred = std::function<bool()>;
    class TimedWaiter
    {
    private:
        bool _done(bool result, uint64_t total_runtime);

    protected:
        uint64_t _timeout_in_ms;
        TimedWaiterPred _fn;
        uint64_t _sleep_time = 0;

        bool _result = false;
        uint64_t _runtime = 0;

        virtual uint64_t _get_current_time() const = 0;
        virtual void _sleep() const = 0;

    public:
        TimedWaiter(TimedWaiterPred fn, uint64_t timeout_in_ms,
                    uint64_t sleep_time);
        bool operator()();
        bool get_result() const;
        uint64_t get_result_runtime() const;
    };
    using TimedWaiterPtr = TimedWaiter *;
    using TimedWaiterSharedPtr = std::shared_ptr<TimedWaiter>;
}; // namespace sabre

#endif // SABRE_TIMED_WAITER_H