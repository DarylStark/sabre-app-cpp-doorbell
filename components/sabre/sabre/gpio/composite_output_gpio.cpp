#include "composite_output_gpio.hpp"

namespace sabre
{
    CompositeOutputGPIO::CompositeOutputGPIO() {}

    void CompositeOutputGPIO::add_gpio(OutputGPIOSharedPtr output_gpio)
    {
        _output_gpios.push_back(output_gpio);
    }

    void CompositeOutputGPIO::reset()
    {
        for (auto &output_gpio : _output_gpios)
            output_gpio->reset();
    }

    void CompositeOutputGPIO::set_high()
    {
        for (auto &output_gpio : _output_gpios)
            output_gpio->set_high();
    }

    void CompositeOutputGPIO::set_low()
    {
        for (auto &output_gpio : _output_gpios)
            output_gpio->set_low();
    }

    void CompositeOutputGPIO::set_level(bool level)
    {
        for (auto &output_gpio : _output_gpios)
            output_gpio->set_level(level);
    }
} // namespace sabre