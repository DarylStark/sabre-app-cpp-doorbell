#include "./factory.h"
#include "exceptions/exceptions.h"

namespace sabre::esp32
{
    sabre::UARTSharedPtr Factory::create_uart_object(uint32_t uart_number,
                                                     int32_t baud_rate,
                                                     int32_t tx_pin,
                                                     int32_t rx_pin) const
    {
        return std::make_shared<UART>(static_cast<uart_port_t>(uart_number),
                                      baud_rate, tx_pin, rx_pin);
    }

    sabre::InputGPIOSharedPtr Factory::create_input_gpio(int32_t pin) const
    {
        return std::make_shared<InputGPIO>(pin);
    }

    sabre::OutputGPIOSharedPtr Factory::create_output_gpio(int32_t pin) const
    {
        return std::make_shared<OutputGPIO>(pin);
    }

    sabre::WifiStationSharedPtr Factory::create_wifi_station() const
    {
        return std::make_shared<WifiStation>();
    }

    sabre::WifiSoftAPSharedPtr Factory::create_wifi_soft_ap() const
    {
        return std::make_shared<WifiSoftAP>();
    }

    sabre::MQTTClientSharedPtr Factory::create_mqtt_client() const
    {
        return std::make_shared<MQTTClient>();
    }
} // namespace sabre::esp32