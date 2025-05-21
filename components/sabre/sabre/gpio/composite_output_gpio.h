#ifndef SABRE_COMPOSITE_OUTPUT_GPIO_H
#define SABRE_COMPOSITE_OUTPUT_GPIO_H

#include <list>
#include <memory>
#include <sabre/gpio/output_gpio.h>

namespace sabre
{
    class CompositeOutputGPIO : public sabre::OutputGPIO
    {
    private:
        std::list<std::shared_ptr<sabre::OutputGPIO>> _output_gpios;

    public:
        CompositeOutputGPIO();

        void add_gpio(std::shared_ptr<sabre::OutputGPIO> output_gpio);

        void reset() override;

        void set_high();
        void set_low();
        void set_level(bool level);
    };
} // namespace sabre

#endif // SABRE_COMPOSITE_OUTPUT_GPIO_H