#ifndef SABRE_ESP32_CLIENTS_MQTT_H
#define SABRE_ESP32_CLIENTS_MQTT_H

#include <mqtt_client.h>
#include <sabre/clients/mqtt.h>
#include <string>

namespace sabre::esp32
{
    class MQTTClient : public sabre::MQTTClient
    {
    private:
        bool _connected = false;
        esp_mqtt_client_handle_t _client = nullptr;

        void _run_subscription(esp_mqtt_event_handle_t event_data);

    public:
        void connect(const std::string &hostname, const std::string &client_id,
                     const std::string &username,
                     const std::string &password) override;

        void disconnect() override;
        void stop() override;

        bool is_connected() const override;

        void publish(const std::string &topic, const std::string &message,
                     sabre::MQTTQoS qos, sabre::MQTTRetain retain) override;
        void subscribe(const std::string &topic, sabre::MQTTCallback fn,
                       sabre::MQTTQoS qos = sabre::MQTTQoS::UNDEFINED) override;

        void handle_event(esp_event_base_t event_base, int32_t event_id,
                          void *event_data);
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_CLIENTS_MQTT_H