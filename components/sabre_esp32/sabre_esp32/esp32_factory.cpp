#include "./esp32_factory.h"

#include <iostream>

namespace sabre::esp32
{
    std::shared_ptr<sabre::UART>
    ESP32Factory::create_uart_object(uint32_t uart_number, int32_t baud_rate,
                                     int32_t tx_pin, int32_t rx_pin) const
    {
        return std::make_shared<sabre::esp32::UART>(UART_NUM_0, baud_rate,
                                                    tx_pin, rx_pin);
    }
} // namespace sabre::esp32