#include <freertos/FreeRTOS.h>
#include <memory>

#include <sabre_esp32/esp32_factory.h>

#include <sabre/clients/mqtt.h>
#include <sabre_esp32/utility/timed_waiter.h>

class Application
{
private:
    std::shared_ptr<sabre::Factory> _factory;
    std::shared_ptr<sabre::WifiStation> _station;
    std::shared_ptr<sabre::MQTTClient> _mqtt_client;
    std::shared_ptr<sabre::OutputGPIO> _led;

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
        _station->connect("<SSID>", "<PASSWORD>");
        sabre::esp32::TimedWaiter w(
            [this]() -> bool { return _station->is_connected(); }, 5000, 100);
        w();
    }

    void _connect_mqtt()
    {
        if (_mqtt_client == nullptr)
            _mqtt_client = _factory->create_mqtt_client();
        _mqtt_client->connect("<BROKER_IP>", "<CLIENT_ID>", "<USERNAME>",
                              "<PASSWORD>");
        sabre::esp32::TimedWaiter w([this]() -> bool
                                    { return _mqtt_client->is_connected(); },
                                    5000, 100);
        w();
        auto topic = _mqtt_client->get_topic("CB-KR23-DBL03-001/command");
        topic->subscribe(std::bind(&Application::_mqtt_command, this,
                                   std::placeholders::_1));
    }

public:
    Application(std::shared_ptr<sabre::Factory> factory) : _factory(factory)
    {
        _led = _factory->create_output_gpio(2);
        _led->set_high();
        _connect_wifi();
        vTaskDelay(pdMS_TO_TICKS(6000));
        _connect_mqtt();
    }
};

extern "C"
{
    void app_main(void)
    {
        Application app(std::make_shared<sabre::esp32::ESP32Factory>());

        while (true)
            vTaskDelay(pdMS_TO_TICKS(1000));

        return;
    }
}