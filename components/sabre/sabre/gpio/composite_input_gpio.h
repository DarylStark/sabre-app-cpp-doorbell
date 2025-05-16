#ifndef _SABRE_COMPOSITE_INPUT_GPIO_H_
#define _SABRE_COMPOSITE_INPUT_GPIO_H_

#include <list>
#include <memory>
#include <sabre/gpio/input_gpio.h>

namespace sabre
{
    class CompositeInputGPIO : public sabre::InputGPIO
    {
    private:
        std::list<std::shared_ptr<sabre::InputGPIO>> _input_gpios;

    public:
        CompositeInputGPIO();

        void add_gpio(std::shared_ptr<sabre::InputGPIO> input_gpio);

        void reset() override;

        bool get_level() const override;
        void enable_pullup() override;
        void enable_pulldown() override;
        void disable_pullup() override;
        void disable_pulldown() override;
        void add_interrupt_handler(std::function<void(int)>);
    };
} // namespace sabre

#endif // _SABRE_COMPOSITE_INPUT_GPIO_H_