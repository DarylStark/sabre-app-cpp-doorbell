#include "mqtt_client.h"

#include <iostream>

void _esp32_mqtt_event_handler(void *handler_args, esp_event_base_t base,
                               int32_t event_id, void *event_data)
{
    using sabre::esp32::MQTTClient;
    MQTTClient *obj = static_cast<MQTTClient *>(handler_args);
    obj->handle_event(base, event_id, event_data);
}

namespace sabre::esp32
{
    void MQTTClient::connect(const std::string &hostname,
                             const std::string &client_id,
                             const std::string &username,
                             const std::string &password)
    {
        std::string uri = "mqtt://" + hostname;

        esp_mqtt_client_config_t mqtt_cfg = {};
        mqtt_cfg.broker.address.uri = uri.c_str();
        mqtt_cfg.credentials.authentication.password = password.c_str();
        mqtt_cfg.credentials.username = username.c_str();
        mqtt_cfg.credentials.client_id = client_id.c_str();
        mqtt_cfg.network.disable_auto_reconnect = true;

        _client = esp_mqtt_client_init(&mqtt_cfg);

        esp_mqtt_client_register_event(_client, MQTT_EVENT_ANY,
                                       _esp32_mqtt_event_handler, this);
        esp_mqtt_client_start(_client);
    }

    void MQTTClient::disconnect()
    {
        if (_client)
            esp_mqtt_client_disconnect(_client);
    }

    void MQTTClient::stop()
    {
        if (_client)
        {
            disconnect();
            esp_mqtt_client_stop(_client);
            esp_mqtt_client_destroy(_client);
            _client = nullptr;
        }
    }

    bool MQTTClient::is_connected() const
    {
        return _connected;
    }

    void MQTTClient::handle_event(esp_event_base_t event_base, int32_t event_id,
                                  void *event_data)
    {
        switch (event_id)
        {
        case MQTT_EVENT_CONNECTED:
            std::cout << "MQTT is connected" << std::endl;
            _connected = true;
            break;
        case MQTT_EVENT_DISCONNECTED:
            _connected = false;
            std::cout << "MQTT is disconnected" << std::endl;
            break;
        default:
            break;
        }
    }
} // namespace sabre::esp32