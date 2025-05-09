#include "./gpio.h"

namespace sabre
{
    void GPIO::set_inverse_level()
    {
        _inverse_level = true;
    }

    void GPIO::set_original_level()
    {
        _inverse_level = false;
    }

    bool GPIO::get_inverse_level() const
    {
        return _inverse_level;
    }
} // namespace sabre