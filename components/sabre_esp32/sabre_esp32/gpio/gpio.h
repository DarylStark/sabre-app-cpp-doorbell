#ifndef _SABRE_ESP32_OUTPUT_GPIO_H_
#define _SABRE_ESP32_OUTPUT_GPIO_H_

#include <cstdint>
#include <sabre/gpio/gpio.h>

namespace sabre::esp32
{
    class GPIO : public sabre::GPIO
    {
    private:
        int32_t _pin_number;

    public:
        GPIO(int32_t pin_number);

        void reset() override;
        void set_high() override;
        void set_low() override;
    };
} // namespace sabre::esp32

#endif