#ifndef SABRE_ESP32_FACTORY_H
#define SABRE_ESP32_FACTORY_H

#include "./gpio/input_gpio.h"
#include "./gpio/output_gpio.h"
#include "./uart/uart.h"
#include "./wifi/wifi_soft_ap.h"
#include "./wifi/wifi_station.h"
#include "clients/mqtt.h"
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

        std::shared_ptr<sabre::InputGPIO> create_input_gpio(int32_t pin) const;
        std::shared_ptr<sabre::OutputGPIO>
        create_output_gpio(int32_t pin) const;
        std::shared_ptr<sabre::WifiStation> create_wifi_station() const;
        std::shared_ptr<sabre::WifiSoftAP> create_wifi_soft_ap() const;

        std::shared_ptr<sabre::MQTTClient> create_mqtt_client() const;
    };
} // namespace sabre::esp32

#endif /* SABRE_ESP32_FACTORY_H */