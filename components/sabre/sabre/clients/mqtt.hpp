#ifndef SABRE_CLIENTS_MQTT_H
#define SABRE_CLIENTS_MQTT_H

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

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
        std::string topic;
        std::string data;
        MQTTQoS qos;
        MQTTRetain retain;
    };
    using MQTTEventPtr = MQTTEvent *;
    using MQTTEventSharedPtr = std::shared_ptr<MQTTEvent>;

    class MQTTClient;

    using MQTTCallback = std::function<void(const MQTTEvent &)>;

    class MQTTTopic
    {
    protected:
        MQTTClient &_client;
        std::string _topic;
        MQTTQoS _default_qos = MQTTQoS::FIRE_AND_FORGET;
        MQTTRetain _default_retain = MQTTRetain::DONT_RETAIN;

    public:
        MQTTTopic(MQTTClient &client, const std::string &topic);
        virtual void publish(const std::string &message,
                             MQTTQoS qos = MQTTQoS::UNDEFINED,
                             MQTTRetain retain = MQTTRetain::UNDEFINED);
        virtual void subscribe(MQTTCallback fn,
                               MQTTQoS qos = MQTTQoS::UNDEFINED);

        void set_default_qos(MQTTQoS qos);
        void set_default_retain(MQTTRetain retain);
    };
    using MQTTTopicPtr = MQTTTopic *;
    using MQTTTopicSharedPtr = std::shared_ptr<MQTTTopic>;
    using MQTTTopicUniquePtr = std::unique_ptr<MQTTTopic>;

    class MQTTClient
    {
    private:
        std::unordered_map<std::string, MQTTCallback> _subscriptions;
        MQTTCallback _default_handler;

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
        virtual void subscribe(const std::string &topic, MQTTCallback fn,
                               MQTTQoS qos = MQTTQoS::UNDEFINED);
        virtual void set_default_handler(MQTTCallback handler);
        void process_received(MQTTEvent event);
        MQTTTopicUniquePtr get_topic(const std::string &topic_name);
    };
    using MQTTClientPtr = MQTTClient *;
    using MQTTClientSharedPtr = std::shared_ptr<MQTTClient>;
}; // namespace sabre

#endif // SABRE_CLIENTS_MQTT_H