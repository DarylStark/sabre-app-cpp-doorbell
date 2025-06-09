#ifndef SABRE_CLIENTS_MQTT_H
#define SABRE_CLIENTS_MQTT_H

#include <memory>
#include <string>

namespace sabre
{
    enum class MQTTQoS
    {
        UNDEFINED = -1,
        FIRE_AND_FORGET = 0,
        AT_LEAST_ONCE = 1,
        EXACTLY_ONCE = 2
    };

    enum class MQTTRetain
    {
        UNDEFINED = -1,
        DONT_RETAIN = 0,
        RETAIN = 1
    };

    class MQTTClient;

    class MQTTTopic
    {
    protected:
        sabre::MQTTClient &_client;
        std::string _topic;
        sabre::MQTTQoS _default_qos = sabre::MQTTQoS::FIRE_AND_FORGET;
        sabre::MQTTRetain _default_retain = sabre::MQTTRetain::DONT_RETAIN;

    public:
        MQTTTopic(sabre::MQTTClient &client, const std::string &topic);
        virtual void
        publish(const std::string &message,
                sabre::MQTTQoS qos = sabre::MQTTQoS::UNDEFINED,
                sabre::MQTTRetain retain = sabre::MQTTRetain::UNDEFINED) = 0;

        void set_default_qos(sabre::MQTTQoS qos);
        void set_default_retain(sabre::MQTTRetain retain);
    };

    class MQTTClient
    {
    public:
        virtual void connect(const std::string &hostname,
                             const std::string &client_id,
                             const std::string &username,
                             const std::string &password) = 0;
        virtual void disconnect() = 0;
        virtual void stop() = 0;
        virtual bool is_connected() const = 0;

        virtual void publish(const std::string &topic,
                             const std::string &message, MQTTQoS qos,
                             MQTTRetain retain) = 0;
        virtual std::unique_ptr<MQTTTopic>
        get_topic(const std::string &topic_name) = 0;
    };
}; // namespace sabre

#endif // SABRE_CLIENTS_MQTT_H