#include "./gpio.h"
#include <driver/gpio.h>

#include <iostream>

namespace sabre::esp32
{
    GPIO::GPIO(int32_t pin_number)
        : _pin_number(pin_number),
          _gpio_num(static_cast<gpio_num_t>(pin_number))
    {
    }

    void GPIO::set_as_output()
    {
        gpio_set_direction(_gpio_num, GPIO_MODE_OUTPUT);
    }

    void GPIO::set_as_input()
    {
        gpio_set_direction(_gpio_num, GPIO_MODE_INPUT);
    }

    void GPIO::reset()
    {
        gpio_reset_pin(_gpio_num);
    }

    void GPIO::set_high()
    {
        gpio_set_level(_gpio_num, 1);
    }

    void GPIO::set_low()
    {
        gpio_set_level(_gpio_num, 0);
    }

    void GPIO::set_level(bool level)
    {
        gpio_set_level(_gpio_num, level ? 1 : 0);
    }

    bool GPIO::get_level() const
    {
        return _inverse_level ? gpio_get_level(_gpio_num) == 0
                              : gpio_get_level(_gpio_num) != 0;
    }

    void GPIO::enable_pullup()
    {
        gpio_pullup_en(_gpio_num);
    }

    void GPIO::enable_pulldown()
    {
        gpio_pulldown_en(_gpio_num);
    }

    void GPIO::disable_pullup()
    {
        gpio_pullup_dis(_gpio_num);
    }

    void GPIO::disable_pulldown()
    {
        gpio_pulldown_dis(_gpio_num);
    }
} // namespace sabre::esp32