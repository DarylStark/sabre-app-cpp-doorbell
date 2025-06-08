#ifndef SABRE_CLIENTS_MQTT_CLIENT_H
#define SABRE_CLIENTS_MQTT_CLIENT_H

#include <string>

namespace sabre
{
    class MQTTClient
    {
        virtual void connect(const std::string &hostname,
                             const std::string &client_id,
                             const std::string &username,
                             const std::string &password) = 0;
        virtual void disconnect() = 0;
        virtual void stop() = 0;
        virtual bool is_connected() const = 0;
    };
}; // namespace sabre

#endif // SABRE_ESP32_CLIENT_MQTT_H