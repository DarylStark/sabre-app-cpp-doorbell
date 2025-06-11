#ifndef SABRE_FACTORY_H
#define SABRE_FACTORY_H

#include "./uart/uart.h"
#include "./uart/uart_output_stream_buffer.h"
#include "clients/mqtt.h"
#include "gpio/input_gpio.h"
#include "gpio/output_gpio.h"
#include "wifi/wifi_soft_ap.h"
#include "wifi/wifi_station.h"
#include <memory>
#include <ostream>

namespace sabre
{
    class Factory
    {
    public:
        virtual UARTSharedPtr create_uart_object(uint32_t uart_number,
                                                 int32_t baud_rate,
                                                 int32_t tx_pin,
                                                 int32_t rx_pin) const = 0;
        virtual UARTStreamBufSharedPtr create_uart_output_stream_buffer(
            uint32_t uart_number, int32_t baud_rate, int32_t tx_pin,
            int32_t rx_pin, size_t buffer_size) const;
        virtual InputGPIOSharedPtr create_input_gpio(int32_t pin) const = 0;
        virtual OutputGPIOSharedPtr create_output_gpio(int32_t pin) const = 0;
        virtual WifiStationSharedPtr create_wifi_station() const = 0;
        virtual WifiSoftAPSharedPtr create_wifi_soft_ap() const = 0;
        virtual MQTTClientSharedPtr create_mqtt_client() const = 0;
    };
    using FactoryPtr = Factory *;
    using FactorySharedPtr = std::shared_ptr<Factory>;
} // namespace sabre

#endif // SABRE_FACTORY_H