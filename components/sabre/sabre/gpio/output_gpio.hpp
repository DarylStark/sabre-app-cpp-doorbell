#ifndef SABRE_OUTPUT_GPIO_H
#define SABRE_OUTPUT_GPIO_H

#include "gpio.hpp"

namespace sabre
{
    class OutputGPIO : public GPIO
    {
    public:
        // Output GPIOs
        virtual void set_high() = 0;
        virtual void set_low() = 0;
        virtual void set_level(bool level) = 0;
    };
    using OutputGPIOPtr = OutputGPIO *;
    using OutputGPIOSharedPtr = std::shared_ptr<OutputGPIO>;
}; // namespace sabre

#endif // SABRE_OUTPUT_GPIO_H