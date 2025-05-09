#include "./gpio.h"
#include <driver/gpio.h>

#include <iostream>

namespace sabre::esp32
{
    GPIO::GPIO(int32_t pin_number) : _pin_number(pin_number) {}

    void GPIO::set_as_output()
    {
        gpio_set_direction(static_cast<gpio_num_t>(_pin_number),
                           GPIO_MODE_OUTPUT);
    }

    void GPIO::set_as_input()
    {
        gpio_set_direction(static_cast<gpio_num_t>(_pin_number),
                           GPIO_MODE_INPUT);
    }

    void GPIO::reset()
    {
        gpio_reset_pin(static_cast<gpio_num_t>(_pin_number));
    }

    void GPIO::set_high()
    {
        gpio_set_level(static_cast<gpio_num_t>(_pin_number), 1);
    }

    void GPIO::set_low()
    {
        gpio_set_level(static_cast<gpio_num_t>(_pin_number), 0);
    }

    void GPIO::set_level(bool level)
    {
        gpio_set_level(static_cast<gpio_num_t>(_pin_number), level ? 1 : 0);
    }

    bool GPIO::get_level() const
    {
        return _inverse_level
                   ? gpio_get_level(static_cast<gpio_num_t>(_pin_number)) == 0
                   : gpio_get_level(static_cast<gpio_num_t>(_pin_number)) != 0;
    }

    void GPIO::enable_pullup()
    {
        gpio_pullup_en(static_cast<gpio_num_t>(_pin_number));
    }

    void GPIO::enable_pulldown()
    {
        gpio_pulldown_en(static_cast<gpio_num_t>(_pin_number));
    }

    void GPIO::disable_pullup()
    {
        gpio_pullup_dis(static_cast<gpio_num_t>(_pin_number));
    }

    void GPIO::disable_pulldown()
    {
        gpio_pulldown_dis(static_cast<gpio_num_t>(_pin_number));
    }
} // namespace sabre::esp32