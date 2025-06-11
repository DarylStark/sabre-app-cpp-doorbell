#ifndef SABRE_ESP32_SERVICE_RUNNER_H
#define SABRE_ESP32_SERVICE_RUNNER_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <functional>
#include <sabre/service_runner/service_runner.h>

namespace sabre::esp32
{
    class ServiceRunner : public sabre::ServiceRunner
    {
    private:
        TaskHandle_t _freertos_handle = nullptr;
        bool _is_running;

        static void _runner(void *b);

    protected:
        virtual void _service() = 0;

    public:
        virtual void start() override;
        virtual void stop() override;
        virtual bool is_running() const;
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_SERVICE_RUNNER_H