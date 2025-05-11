#include "./gpio.h"
#include <driver/gpio.h>

namespace sabre::esp32
{
    GPIO::GPIO(int32_t pin_number)
        : _pin_number(pin_number),
          _gpio_num(static_cast<gpio_num_t>(pin_number))
    {
    }

    void GPIO::reset()
    {
        gpio_reset_pin(_gpio_num);
    }
} // namespace sabre::esp32