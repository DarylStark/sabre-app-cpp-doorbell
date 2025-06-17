#ifndef SABRE_INPUT_GPIO_H
#define SABRE_INPUT_GPIO_H

#include "gpio.hpp"
#include <functional>
#include <memory>

namespace sabre
{
    using ISRHandler = std::function<void(int)>;

    struct ISRConfig
    {
        ISRHandler handler;
        int gpio;
    };
    using ISRConfigPtr = ISRConfig *;
    using ISRConfigSharedPtr = std::shared_ptr<ISRConfig>;

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
        virtual bool _get_level() const = 0;

    public:
        // Input GPIOs
        virtual bool get_level() const;
        virtual void set_inverse_level(bool level = false);
        virtual bool get_inverse_level() const;
        virtual void enable_pullup() = 0;
        virtual void enable_pulldown() = 0;
        virtual void disable_pullup() = 0;
        virtual void disable_pulldown() = 0;
        virtual void add_interrupt_handler(ISRHandler, ISRTrigger) = 0;
    };
    using InputGPIOPtr = InputGPIO *;
    using InputGPIOSharedPtr = std::shared_ptr<InputGPIO>;
}; // namespace sabre

#endif // SABRE_INPUT_GPIO_H