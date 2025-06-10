#include "mqtt.h"

namespace sabre
{
    MQTTTopic::MQTTTopic(sabre::MQTTClient &client, const std::string &topic)
        : _client(client), _topic(topic)
    {
    }

    void MQTTTopic::set_default_qos(sabre::MQTTQoS qos)
    {
        if (qos == sabre::MQTTQoS::UNDEFINED)
            return;
        _default_qos = qos;
    }

    void MQTTTopic::set_default_retain(sabre::MQTTRetain retain)
    {
        if (retain == sabre::MQTTRetain::UNDEFINED)
            return;
        _default_retain = retain;
    }

    void MQTTTopic::subscribe(std::function<void(const sabre::MQTTEvent &)> fn,
                              sabre::MQTTQoS qos)
    {
        _client.subscribe(_topic, fn, qos);
    }

    void MQTTClient::subscribe(const std::string &topic,
                               std::function<void(const MQTTEvent &)> fn,
                               sabre::MQTTQoS qos)
    {
        if (qos == sabre::MQTTQoS::UNDEFINED)
            qos = sabre::MQTTQoS::EXACTLY_ONCE;

        _subscriptions[topic] = fn;
    }
} // namespace sabre