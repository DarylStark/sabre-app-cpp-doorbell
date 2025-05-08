#include "./gpio.h"
#include <driver/gpio.h>

namespace sabre::esp32
{
    GPIO::GPIO(int32_t pin_number) : _pin_number(pin_number)
    {
        gpio_set_direction(static_cast<gpio_num_t>(_pin_number),
                           GPIO_MODE_OUTPUT);
    }

    void GPIO::set_high()
    {
        gpio_set_level(static_cast<gpio_num_t>(_pin_number), 1);
    }

    void GPIO::set_low()
    {
        gpio_set_level(static_cast<gpio_num_t>(_pin_number), 0);
    }

    void GPIO::reset()
    {
        gpio_reset_pin(static_cast<gpio_num_t>(_pin_number));
    }
} // namespace sabre::esp32