#include "./input_gpio.h"
#include <driver/gpio.h>
#include <iostream>

namespace sabre::esp32
{
    std::unordered_map<sabre::ISRTrigger, gpio_int_type_t>
        InputGPIO::_trigger_map = {
            {sabre::ISRTrigger::RISING, GPIO_INTR_POSEDGE},
            {sabre::ISRTrigger::FALLING, GPIO_INTR_NEGEDGE},
            {sabre::ISRTrigger::BOTH, GPIO_INTR_ANYEDGE},
            {sabre::ISRTrigger::LOW, GPIO_INTR_LOW_LEVEL},
            {sabre::ISRTrigger::HIGH, GPIO_INTR_HIGH_LEVEL}};

    InputGPIO::InputGPIO(int32_t pin_number)
        : _pin_number(pin_number),
          _gpio_num(static_cast<gpio_num_t>(pin_number))
    {
        gpio_set_direction(_gpio_num, GPIO_MODE_INPUT);
    }

    void InputGPIO::reset()
    {
        gpio_reset_pin(_gpio_num);
    }

    bool InputGPIO::get_level() const
    {
        return gpio_get_level(_gpio_num) == static_cast<int>(!_inverse_level);
    }

    void InputGPIO::enable_pullup()
    {
        gpio_pullup_en(_gpio_num);
    }

    void InputGPIO::enable_pulldown()
    {
        gpio_pulldown_en(_gpio_num);
    }

    void InputGPIO::disable_pullup()
    {
        gpio_pullup_dis(_gpio_num);
    }

    void InputGPIO::disable_pulldown()
    {
        gpio_pulldown_dis(_gpio_num);
    }

    void InputGPIO::add_interrupt_handler(std::function<void(int)> handler,
                                          sabre::ISRTrigger trigger)
    {
        _config = std::make_shared<sabre::ISRConfig>();
        _config->handler = handler;
        _config->gpio = static_cast<int32_t>(_gpio_num);

        gpio_set_intr_type(_gpio_num, _trigger_map.at(trigger));
        std::cout << "GPIO " << _pin_number << " interrupt type set to "
                  << static_cast<int>(_trigger_map.at(trigger)) << std::endl;
        gpio_isr_handler_add(
            _gpio_num,
            [](void *config)
            {
                auto cfg = static_cast<sabre::ISRConfig *>(config);
                auto func = cfg->handler;
                func(cfg->gpio);
            },
            static_cast<void *>(_config.get()));
    }
} // namespace sabre::esp32