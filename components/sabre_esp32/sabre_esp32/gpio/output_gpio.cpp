#include "./output_gpio.h"
#include <driver/gpio.h>

namespace sabre::esp32
{
    OutputGPIO::OutputGPIO(int32_t pin_number)
        : _pin_number(pin_number),
          _gpio_num(static_cast<gpio_num_t>(pin_number))
    {
        gpio_set_direction(_gpio_num, GPIO_MODE_OUTPUT);
    }

    void OutputGPIO::set_as_output()
    {
        gpio_set_direction(_gpio_num, GPIO_MODE_OUTPUT);
    }

    void OutputGPIO::set_as_input()
    {
        gpio_set_direction(_gpio_num, GPIO_MODE_INPUT);
    }

    void OutputGPIO::reset()
    {
        gpio_reset_pin(_gpio_num);
    }

    void OutputGPIO::set_high()
    {
        gpio_set_level(_gpio_num, 1);
    }

    void OutputGPIO::set_low()
    {
        gpio_set_level(_gpio_num, 0);
    }

    void OutputGPIO::set_level(bool level)
    {
        gpio_set_level(_gpio_num, level ? 1 : 0);
    }
} // namespace sabre::esp32