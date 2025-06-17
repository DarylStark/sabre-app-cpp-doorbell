#ifndef SABRE_COMPOSITE_INPUT_GPIO_H
#define SABRE_COMPOSITE_INPUT_GPIO_H

#include <list>
#include <memory>
#include <sabre/gpio/input_gpio.hpp>

namespace sabre
{
    class CompositeInputGPIO : public InputGPIO
    {
    private:
        std::list<InputGPIOSharedPtr> _input_gpios;

    public:
        CompositeInputGPIO();

        void add_gpio(InputGPIOSharedPtr input_gpio);

        void reset() override;

        bool get_level() const override;
        void enable_pullup() override;
        void enable_pulldown() override;
        void disable_pullup() override;
        void disable_pulldown() override;
        void add_interrupt_handler(ISRHandler, ISRTrigger) override;
    };
    using CompositeInputGPIOPtr = CompositeInputGPIO *;
    using CompositeInputGPIOSharedPtr = std::shared_ptr<CompositeInputGPIO>;
} // namespace sabre

#endif // SABRE_COMPOSITE_INPUT_GPIO_H