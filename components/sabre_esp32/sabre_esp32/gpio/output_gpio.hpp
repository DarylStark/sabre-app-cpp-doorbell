#ifndef SABRE_ESP32_OUTPUT_GPIO_H
#define SABRE_ESP32_OUTPUT_GPIO_H

#include <cstdint>
#include <driver/gpio.h>
#include <memory>
#include <sabre/gpio/output_gpio.hpp>

namespace sabre::esp32
{
    class OutputGPIO : public sabre::OutputGPIO
    {
    private:
        int32_t _pin_number;
        gpio_num_t _gpio_num;

    public:
        OutputGPIO(int32_t pin_number);
        ~OutputGPIO();

        void reset() override;

        void set_high() override;
        void set_low() override;
        void set_level(bool level) override;
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_OUTPUT_GPIO_H