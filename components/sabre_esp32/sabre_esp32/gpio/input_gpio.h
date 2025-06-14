#ifndef SABRE_ESP32_INPUT_GPIO_H
#define SABRE_ESP32_INPUT_GPIO_H

#include <cstdint>
#include <driver/gpio.h>
#include <map>
#include <memory>
#include <sabre/gpio/input_gpio.h>

namespace sabre::esp32
{
    class InputGPIO : public sabre::InputGPIO
    {
    private:
        int32_t _pin_number;
        gpio_num_t _gpio_num;
        ISRConfigSharedPtr _config;

        static std::unordered_map<sabre::ISRTrigger, gpio_int_type_t>
            _trigger_map;
        static bool _isr_service_installed;

    public:
        InputGPIO(int32_t pin_number);
        ~InputGPIO();

        void reset() override;

        bool get_level() const override;
        void enable_pullup() override;
        void enable_pulldown() override;
        void disable_pullup() override;
        void disable_pulldown() override;
        void add_interrupt_handler(sabre::ISRHandler,
                                   sabre::ISRTrigger trigger);
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_INPUT_GPIO_H