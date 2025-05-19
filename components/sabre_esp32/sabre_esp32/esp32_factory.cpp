#include "./esp32_factory.h"

namespace sabre::esp32
{
    std::shared_ptr<sabre::UART>
    ESP32Factory::create_uart_object(uint32_t uart_number, int32_t baud_rate,
                                     int32_t tx_pin, int32_t rx_pin) const
    {
        return std::make_shared<sabre::esp32::UART>(
            static_cast<uart_port_t>(uart_number), baud_rate, tx_pin, rx_pin);
    }

    std::shared_ptr<sabre::InputGPIO>
    ESP32Factory::create_input_gpio(int32_t pin) const
    {
        return std::make_shared<sabre::esp32::InputGPIO>(pin);
    }

    std::shared_ptr<sabre::OutputGPIO>
    ESP32Factory::create_output_gpio(int32_t pin) const
    {
        return std::make_shared<OutputGPIO>(pin);
    }
} // namespace sabre::esp32