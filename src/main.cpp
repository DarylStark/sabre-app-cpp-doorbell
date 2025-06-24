#include <freertos/FreeRTOS.h>

#include <sabre_esp32/factory.hpp>

#include <sabre/clients/mqtt.hpp>
#include <sabre_esp32/utility/wait_for.hpp>

#include "credentials.h"

#include "esp_sntp.h"
#include <iostream>

#include <sabre_esp32/clients/ntp.hpp>
#include <sabre_esp32/system/wall_clock.hpp>

class Application
{
private:
    sabre::FactorySharedPtr _factory;
    sabre::WifiStationSharedPtr _station;
    sabre::MQTTClientSharedPtr _mqtt_client;
    sabre::OutputGPIOSharedPtr _led;
    sabre::InputGPIOSharedPtr _button;

    std::shared_ptr<sabre::NTPClient> _ntp_client;

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
        auto w = _factory->create_wait_for(
            [this]() -> bool { return _station->is_connected(); }, 5000, 100);
        (*w)();
        auto w2 = _factory->create_wait_for(
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
        auto w = _factory->create_wait_for(
            [this]() -> bool { return _mqtt_client->is_connected(); }, 5000,
            100);
        (*w)();
        auto topic = _mqtt_client->get_topic("CB-KR23-DBL03-001/command");
        topic->subscribe(std::bind(&Application::_mqtt_command, this,
                                   std::placeholders::_1));
    }

    void _isr_button(int s)
    {
        _led->set_low();
    }

    void _connect_ntp()
    {
        _ntp_client = std::make_shared<sabre::esp32::NTPClient>("pool.ntp.org");
        _ntp_client->start();
        auto w = _factory->create_wait_for(
            [this]() -> bool { return _ntp_client->is_synchronized(); }, 5000,
            100);
        (*w)();
    }

public:
    Application(sabre::FactorySharedPtr factory) : _factory(factory)
    {
        _led = _factory->create_output_gpio(2);
        _button = factory->create_input_gpio(26);
        _button->enable_pullup();
        _button->add_interrupt_handler(
            std::bind(&Application::_isr_button, this, std::placeholders::_1),
            sabre::ISRTrigger::RISING);
        _led->set_high();
        _connect_wifi();
        _connect_mqtt();
        _connect_ntp();

        std::unique_ptr<sabre::WallClock> wc =
            std::make_unique<sabre::esp32::WallClock>();
        while (true)
        {
            std::cout << "Current time: " << wc->now_ms()
                      << " ms since 1970-01-01 00:00:00 UTC" << std::endl;
            vTaskDelay(pdMS_TO_TICKS(500));
        }
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