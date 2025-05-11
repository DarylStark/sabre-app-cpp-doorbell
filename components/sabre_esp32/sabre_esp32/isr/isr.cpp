#include "./isr.h"

#include "driver/gpio.h"

namespace sabre::esp32
{
    ISR::ISR(int32_t gpio_number) : _gpio_number(gpio_number)
    {
        gpio_install_isr_service(0);
    }

    void handler()
    {
        // HANDLE THE ISR`
    }

    void ISR::set_handler(void (*handler)(int))
    {
        _config = std::make_shared<ISRConfig>();
        _config->handler = handler;
        _config->gpio = _gpio_number;

        gpio_set_intr_type(static_cast<gpio_num_t>(_gpio_number),
                           GPIO_INTR_ANYEDGE);
        gpio_isr_handler_add(
            static_cast<gpio_num_t>(_gpio_number),
            [](void *a)
            {
                auto cfg = static_cast<ISRConfig *>(a);
                auto func = cfg->handler;
                func(cfg->gpio);
            },
            static_cast<void *>(_config.get()));
    }
}; // namespace sabre::esp32