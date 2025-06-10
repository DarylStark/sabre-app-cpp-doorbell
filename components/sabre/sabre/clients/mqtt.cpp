#include "mqtt.h"

namespace sabre
{
    MQTTTopic::MQTTTopic(sabre::MQTTClient &client, const std::string &topic)
        : _client(client), _topic(topic)
    {
    }

    void MQTTTopic::publish(const std::string &message, sabre::MQTTQoS qos,
                            sabre::MQTTRetain retain)
    {
        if (qos == sabre::MQTTQoS::UNDEFINED)
            qos = _default_qos;
        if (retain == sabre::MQTTRetain::UNDEFINED)
            retain = _default_retain;

        _client.publish(_topic, message, qos, retain);
    }

    void MQTTTopic::subscribe(std::function<void(const sabre::MQTTEvent &)> fn,
                              sabre::MQTTQoS qos)
    {
        _client.subscribe(_topic, fn, qos);
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

    void MQTTClient::subscribe(const std::string &topic,
                               std::function<void(const MQTTEvent &)> fn,
                               sabre::MQTTQoS qos)
    {
        if (qos == sabre::MQTTQoS::UNDEFINED)
            qos = sabre::MQTTQoS::EXACTLY_ONCE;

        _subscriptions[topic] = fn;
    }

    std::unique_ptr<sabre::MQTTTopic>
    MQTTClient::get_topic(const std::string &topic_name)
    {
        return std::make_unique<sabre::MQTTTopic>(*this, topic_name);
    }
} // namespace sabre