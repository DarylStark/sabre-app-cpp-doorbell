#include "./gpio.h"
#include <driver/gpio.h>

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
        return gpio_get_level(_gpio_num) == static_cast<int>(!_inverse_level);
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

    void GPIO::add_interrupt_handler(void (*handler)(int))
    {
        _config = std::make_shared<ISRConfig2>();
        _config->handler = handler;
        _config->gpio = static_cast<int32_t>(_gpio_num);

        gpio_set_intr_type(_gpio_num, GPIO_INTR_ANYEDGE);
        gpio_isr_handler_add(
            static_cast<gpio_num_t>(_gpio_num),
            [](void *config)
            {
                auto cfg = static_cast<ISRConfig2 *>(config);
                auto func = cfg->handler;
                func(cfg->gpio);
            },
            static_cast<void *>(_config.get()));
    }
} // namespace sabre::esp32