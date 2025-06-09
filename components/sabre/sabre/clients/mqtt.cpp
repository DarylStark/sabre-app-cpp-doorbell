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
} // namespace sabre