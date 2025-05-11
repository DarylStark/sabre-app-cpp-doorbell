#ifndef _SABRE_ESP32_INPUT_GPIO_H_
#define _SABRE_ESP32_INPUT_GPIO_H_

#include <cstdint>
#include <driver/gpio.h>
#include <memory>
#include <sabre/gpio/input_gpio.h>

namespace sabre::esp32
{
    class InputGPIO : public sabre::InputGPIO
    {
    private:
        int32_t _pin_number;
        gpio_num_t _gpio_num;
        std::shared_ptr<sabre::ISRConfig> _config;

    public:
        InputGPIO(int32_t pin_number);

        void reset() override;

        bool get_level() const override;
        void enable_pullup() override;
        void enable_pulldown() override;
        void disable_pullup() override;
        void disable_pulldown() override;
        void add_interrupt_handler(void (*handler)(int));
    };
} // namespace sabre::esp32

#endif // _SABRE_ESP32_INPUT_GPIO_H_