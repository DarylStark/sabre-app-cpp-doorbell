#ifndef SABRE_ESP32_FACTORY_H
#define SABRE_ESP32_FACTORY_H

#include "clients/mqtt.h"
#include "gpio/input_gpio.h"
#include "gpio/output_gpio.h"
#include "uart/uart.h"
#include "utility/timed_waiter.h"
#include "wifi/wifi_soft_ap.h"
#include "wifi/wifi_station.h"
#include <map>
#include <memory>
#include <sabre/factory.h>

namespace sabre::esp32
{
    class Factory : public sabre::Factory
    {
    private:
        std::map<uint16_t, std::unique_ptr<std::ostream>> _output_streams;

    public:
        sabre::UARTSharedPtr create_uart_object(uint32_t uart_number,
                                                int32_t baud_rate,
                                                int32_t tx_pin,
                                                int32_t rx_pin) const override;
        sabre::InputGPIOSharedPtr create_input_gpio(int32_t pin) const;
        sabre::OutputGPIOSharedPtr create_output_gpio(int32_t pin) const;
        sabre::WifiStationSharedPtr create_wifi_station() const;
        sabre::WifiSoftAPSharedPtr create_wifi_soft_ap() const;
        sabre::MQTTClientSharedPtr create_mqtt_client() const;
        sabre::TimedWaiterSharedPtr
        create_timed_waiter(TimedWaiterPred fn, uint64_t timeout_in_ms,
                            uint64_t sleep_time) const;
    };
} // namespace sabre::esp32

#endif /* SABRE_ESP32_FACTORY_H */