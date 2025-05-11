#ifndef _SABRE_ESP32_GPIO_H_
#define _SABRE_ESP32_GPIO_H_

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

    public:
        GPIO(int32_t pin_number);

        void reset() override;
    };
} // namespace sabre::esp32

#endif // _SABRE_ESP32_GPIO_H_