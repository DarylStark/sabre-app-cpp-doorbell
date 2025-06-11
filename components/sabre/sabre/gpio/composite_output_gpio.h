#ifndef SABRE_COMPOSITE_OUTPUT_GPIO_H
#define SABRE_COMPOSITE_OUTPUT_GPIO_H

#include <list>
#include <memory>
#include <sabre/gpio/output_gpio.h>

namespace sabre
{
    class CompositeOutputGPIO : public OutputGPIO
    {
    private:
        std::list<OutputGPIOSharedPtr> _output_gpios;

    public:
        CompositeOutputGPIO();

        void add_gpio(OutputGPIOSharedPtr output_gpio);

        void reset() override;

        void set_high();
        void set_low();
        void set_level(bool level);
    };
    using CompositeOutputGPIOPtr = CompositeOutputGPIO *;
    using CompositeOutputGPIOSharedPtr = std::shared_ptr<CompositeOutputGPIO>;
} // namespace sabre

#endif // SABRE_COMPOSITE_OUTPUT_GPIO_H