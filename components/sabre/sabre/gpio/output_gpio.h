#ifndef _SABRE_OUTPUT_GPIO_H_
#define _SABRE_OUTPUT_GPIO_H_

#include "./gpio.h"

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
}; // namespace sabre

#endif // _SABRE_OUTPUT_GPIO_H_