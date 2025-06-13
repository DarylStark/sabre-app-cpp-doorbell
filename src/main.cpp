#include <freertos/FreeRTOS.h>

#include <sabre_esp32/factory.h>

#include <sabre/clients/mqtt.h>
#include <sabre_esp32/utility/timed_waiter.h>

#include "credentials.h"

class Application
{
private:
    sabre::FactorySharedPtr _factory;
    sabre::WifiStationSharedPtr _station;
    sabre::MQTTClientSharedPtr _mqtt_client;
    sabre::OutputGPIOSharedPtr _led;

    void _mqtt_command(sabre::MQTTEvent e)
    {
        if (e.data == "on")
            _led->set_high();
        else if (e.data == "off")
            _led->set_low();
    }

    void _connect_wifi()
    {
        if (_station == nullptr)
            _station = _factory->create_wifi_station();
        _station->connect(WIFI_SSID, WIFI_PASS);
        auto w = _factory->create_timed_waiter(
            [this]() -> bool { return _station->is_connected(); }, 5000, 100);
        (*w)();
        auto w2 = _factory->create_timed_waiter(
            [this]() -> bool { return _station->has_ipv4_address(); }, 5000,
            100);
        (*w2)();
    }

    void _connect_mqtt()
    {
        if (_mqtt_client == nullptr)
            _mqtt_client = _factory->create_mqtt_client();
        _mqtt_client->connect(MQTT_HOSTNAME, MQTT_CLIENT_ID, MQTT_USERNAME,
                              MQTT_PASSWORD);
        auto w = _factory->create_timed_waiter(
            [this]() -> bool { return _mqtt_client->is_connected(); }, 5000,
            100);
        (*w)();
        auto topic = _mqtt_client->get_topic("CB-KR23-DBL03-001/command");
        topic->subscribe(std::bind(&Application::_mqtt_command, this,
                                   std::placeholders::_1));
    }

public:
    Application(sabre::FactorySharedPtr factory) : _factory(factory)
    {
        _led = _factory->create_output_gpio(2);
        _led->set_high();
        _connect_wifi();
        _connect_mqtt();
    }
};

extern "C"
{
    void app_main(void)
    {
        Application app(std::make_shared<sabre::esp32::Factory>());

        while (true)
            vTaskDelay(pdMS_TO_TICKS(10000));

        return;
    }
}