#include <freertos/FreeRTOS.h>
#include <functional>
#include <iostream>
#include <memory>
#include <sabre_esp32/gpio/output_gpio.h>
#include <sabre_esp32/service_runner/service_runner.h>

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
    Application() : _service(std::make_shared<MyService>(500))
    {
        _service->start();
    }
};

extern "C"
{
    void app_main(void)
    {
        Application app;

        while (true)
            vTaskDelay(pdMS_TO_TICKS(1000));

        return;
    }
}