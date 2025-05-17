#ifndef _SABRE_INPUT_GPIO_H_
#define _SABRE_INPUT_GPIO_H_

#include "./gpio.h"
#include <functional>

namespace sabre
{
    struct ISRConfig
    {
        std::function<void(int)> handler;
        int gpio;
    };

    enum class ISRTrigger : int
    {
        RISING,
        FALLING,
        BOTH,
        LOW,
        HIGH
    };

    class InputGPIO : public GPIO
    {
    protected:
        bool _inverse_level = false;

    public:
        // Input GPIOs
        virtual bool get_level() const = 0;
        virtual void set_inverse_level();
        virtual void set_original_level();
        virtual bool get_inverse_level() const;
        virtual void enable_pullup() = 0;
        virtual void enable_pulldown() = 0;
        virtual void disable_pullup() = 0;
        virtual void disable_pulldown() = 0;
        virtual void add_interrupt_handler(std::function<void(int)>,
                                           ISRTrigger) = 0;
    };
}; // namespace sabre

#endif // _SABRE_INPUT_GPIO_H_