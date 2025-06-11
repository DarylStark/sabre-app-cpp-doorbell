#ifndef SABRE_CLIENTS_MQTT_H
#define SABRE_CLIENTS_MQTT_H

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

using std::shared_ptr;
using std::string;
using std::unique_ptr;

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

    struct MQTTEvent
    {
        string topic;
        string data;
        MQTTRetain retain;
        MQTTQoS qos;
    };
    using MQTTEventPtr = MQTTEvent *;
    using MQTTEventSharedPtr = shared_ptr<MQTTEvent>;

    class MQTTClient;

    using MQTTCallback = std::function<void(const MQTTEvent &)>;

    class MQTTTopic
    {
    protected:
        MQTTClient &_client;
        string _topic;
        MQTTQoS _default_qos = MQTTQoS::FIRE_AND_FORGET;
        MQTTRetain _default_retain = MQTTRetain::DONT_RETAIN;

    public:
        MQTTTopic(MQTTClient &client, const string &topic);
        virtual void publish(const string &message,
                             MQTTQoS qos = MQTTQoS::UNDEFINED,
                             MQTTRetain retain = MQTTRetain::UNDEFINED);
        virtual void subscribe(MQTTCallback fn,
                               MQTTQoS qos = MQTTQoS::UNDEFINED);

        void set_default_qos(MQTTQoS qos);
        void set_default_retain(MQTTRetain retain);
    };
    using MQTTTopicPtr = MQTTTopic *;
    using MQTTTopicSharedPtr = shared_ptr<MQTTTopic>;
    using MQTTTopicUniquePtr = unique_ptr<MQTTTopic>;

    class MQTTClient
    {
    protected:
        std::unordered_map<string, MQTTCallback> _subscriptions;

    public:
        virtual void connect(const string &hostname, const string &client_id,
                             const string &username,
                             const string &password) = 0;
        virtual void disconnect() = 0;
        virtual void stop() = 0;
        virtual bool is_connected() const = 0;

        virtual void publish(const string &topic, const string &message,
                             MQTTQoS qos, MQTTRetain retain) = 0;
        virtual void subscribe(const string &topic, MQTTCallback fn,
                               MQTTQoS qos = MQTTQoS::UNDEFINED);
        MQTTTopicUniquePtr get_topic(const string &topic_name);
    };
    using MQTTClientPtr = MQTTClient *;
    using MQTTClientSharedPtr = shared_ptr<MQTTClient>;
}; // namespace sabre

#endif // SABRE_CLIENTS_MQTT_H