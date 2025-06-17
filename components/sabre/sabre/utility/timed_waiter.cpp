#include "timed_waiter.hpp"

namespace sabre
{

    bool TimedWaiter::_done(bool result, uint64_t total_runtime)
    {
        _runtime = total_runtime;
        _result = result;
        return result;
    }

    TimedWaiter::TimedWaiter(TimedWaiterPred fn, uint64_t timeout_in_ms,
                             uint64_t sleep_time)
        : _timeout_in_ms(timeout_in_ms), _fn(fn), _sleep_time(sleep_time)
    {
    }

    bool TimedWaiter::operator()()
    {
        uint64_t starttime = _get_current_time();

        while (_timeout_in_ms > _get_current_time() - starttime)
        {
            if (_fn())
                return _done(true, _get_current_time() - starttime);
            _sleep();
        }
        return _done(false, _get_current_time() - starttime);
    }

    bool TimedWaiter::get_result() const
    {
        return _result;
    }

    uint64_t TimedWaiter::get_result_runtime() const
    {
        return _runtime;
    }
}; // namespace sabre