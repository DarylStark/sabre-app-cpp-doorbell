#ifndef _SABRE_ESP32_ISR_H_
#define _SABRE_ESP32_ISR_H_

#include <memory>
#include <sabre/isr/isr.h>

namespace sabre::esp32
{
    // TODO: Move this struct to sabre
    struct ISRConfig
    {
        void (*handler)(int);
        int gpio;
    };

    class ISR : public sabre::ISR
    {
    private:
        std::shared_ptr<ISRConfig> _config;
        int32_t _gpio_number;

    public:
        ISR(int32_t gpio_number);
        void set_handler(void (*handler)(int));
    };
} // namespace sabre::esp32

#endif // _SABRE_ESP32_ISR_H_