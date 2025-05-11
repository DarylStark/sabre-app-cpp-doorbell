#ifndef _SABRE_ESP32_OUTPUT_GPIO_H_
#define _SABRE_ESP32_OUTPUT_GPIO_H_

#include <cstdint>
#include <driver/gpio.h>
#include <memory>
#include <sabre/gpio/gpio.h>

namespace sabre::esp32
{
    class GPIO : public sabre::GPIO
    {
    private:
        int32_t _pin_number;
        gpio_num_t _gpio_num;
        std::shared_ptr<sabre::ISRConfig> _config;

    public:
        GPIO(int32_t pin_number);

        void reset() override;
        void set_as_output();
        void set_as_input();

        void set_high() override;
        void set_low() override;
        void set_level(bool level) override;

        bool get_level() const override;
        void enable_pullup() override;
        void enable_pulldown() override;
        void disable_pullup() override;
        void disable_pulldown() override;
        void add_interrupt_handler(void (*handler)(int));
    };
} // namespace sabre::esp32

#endif