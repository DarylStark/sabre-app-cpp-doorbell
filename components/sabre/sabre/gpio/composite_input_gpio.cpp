#include "composite_input_gpio.h"

namespace sabre
{
    CompositeInputGPIO::CompositeInputGPIO() {}

    void CompositeInputGPIO::add_gpio(InputGPIOSharedPtr input_gpio)
    {
        _input_gpios.push_back(input_gpio);
    }

    void CompositeInputGPIO::reset()
    {
        for (auto &input_gpio : _input_gpios)
            input_gpio->reset();
    }

    bool CompositeInputGPIO::get_level() const
    {
        for (const auto &input_gpio : _input_gpios)
            if (!input_gpio->get_level())
                return false;
        return true;
    }

    void CompositeInputGPIO::enable_pullup()
    {
        for (auto &input_gpio : _input_gpios)
            input_gpio->enable_pullup();
    }

    void CompositeInputGPIO::enable_pulldown()
    {
        for (auto &input_gpio : _input_gpios)
            input_gpio->enable_pulldown();
    }

    void CompositeInputGPIO::disable_pullup()
    {
        for (auto &input_gpio : _input_gpios)
            input_gpio->disable_pullup();
    }

    void CompositeInputGPIO::disable_pulldown()
    {
        for (auto &input_gpio : _input_gpios)
            input_gpio->disable_pulldown();
    }

    void CompositeInputGPIO::add_interrupt_handler(ISRHandler handler,
                                                   ISRTrigger trigger)
    {
        for (auto &input_gpio : _input_gpios)
            input_gpio->add_interrupt_handler(handler, trigger);
    }
} // namespace sabre