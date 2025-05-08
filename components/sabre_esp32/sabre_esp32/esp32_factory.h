#ifndef _SABRE_ESP32_FACTORY_H_
#define _SABRE_ESP32_FACTORY_H_

#include "./uart/uart.h"
#include <map>
#include <memory>
#include <sabre/factory.h>

namespace sabre::esp32
{
    class ESP32Factory : public sabre::Factory
    {
    private:
        std::map<uint16_t, std::unique_ptr<std::ostream>> _output_streams;

    public:
        std::shared_ptr<sabre::UART>
        create_uart_object(uint32_t uart_number, int32_t baud_rate,
                           int32_t tx_pin, int32_t rx_pin) const override;
    };
} // namespace sabre::esp32

#endif /* _SABRE_ESP32_FACTORY_H_ */