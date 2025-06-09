#include <freertos/FreeRTOS.h>
#include <functional>
#include <iostream>
#include <memory>
#include <sabre_esp32/gpio/output_gpio.h>
#include <sabre_esp32/service_runner/service_runner.h>

#include <sabre_esp32/clients/mqtt.h>
#include <sabre_esp32/utility/timed_waiter.h>
#include <sabre_esp32/wifi/wifi_station.h>

class MyService : public sabre::esp32::ServiceRunner
{
private:
    bool _state = false;
    sabre::esp32::OutputGPIO _gpio;
    uint16_t _interval;

protected:
    void _service() override
    {
        while (true)
        {
            _state = !_state;
            _gpio.set_level(_state);
            vTaskDelay(pdMS_TO_TICKS(_interval));
        }
    }

public:
    MyService(uint16_t interval) : _gpio(2), _interval(interval) {}
    void set_interval(uint16_t interval)
    {
        _interval = interval;
    }
};

class Application
{
    std::shared_ptr<MyService> _service;

public:
    Application()
    {
        using namespace sabre::esp32;

        WifiStation wifi;
        MQTTClient mqtt;

        wifi.connect("<ssid>", "<password>");
        TimedWaiter w([&wifi]() { return wifi.is_connected(); }, 5000, 100);
        if (!w())
            return;

        std::cout << "Wifi connected!" << std::endl;
        vTaskDelay(pdMS_TO_TICKS(5000));

        mqtt.connect("<hostname>", "<client_id>", "<username>", "<password>");

        if (!TimedWaiter([&mqtt]() { return mqtt.is_connected(); }, 5000,
                         100)())
            return;

        std::cout << "MQTT connected" << std::endl;

        vTaskDelay(pdMS_TO_TICKS(500));

        auto topic = mqtt.get_topic("my_topic/test/test");
        topic->set_default_qos(sabre::MQTTQoS::EXACTLY_ONCE);
        topic->set_default_retain(sabre::MQTTRetain::RETAIN);
        topic->publish("Hi there from my special object as ptr",
                       sabre::MQTTQoS::FIRE_AND_FORGET);

        while (true)
            vTaskDelay(pdMS_TO_TICKS(1000));
    }
};

extern "C"
{
    void app_main(void)
    {
        Application app;

        return;
    }
}