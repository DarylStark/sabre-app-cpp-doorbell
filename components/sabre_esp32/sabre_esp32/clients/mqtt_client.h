#ifndef SABRE_ESP32_CLIENTS_MQTT_H
#define SABRE_ESP32_CLIENTS_MQTT_H

#include <mqtt_client.h>
#include <sabre/clients/mqtt_client.h>
#include <string>

namespace sabre::esp32
{
    class MQTTClient : public sabre::MQTTClient
    {
    private:
        bool _connected = false;
        esp_mqtt_client_handle_t _client = nullptr;

    public:
        void connect(const std::string &hostname, const std::string &client_id,
                     const std::string &username,
                     const std::string &password) override;

        void disconnect() override;
        void stop() override;

        bool is_connected() const override;

        void handle_event(esp_event_base_t event_base, int32_t event_id,
                          void *event_data);
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_CLIENTS_MQTT_H