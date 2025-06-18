#ifndef SABRE_ESP32_SERVICE_H
#define SABRE_ESP32_SERVICE_H

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <functional>
#include <sabre/service/service.hpp>

namespace sabre::esp32
{
    class Service : public sabre::Service
    {
    private:
        TaskHandle_t _freertos_handle = nullptr;
        static void _runner(void *b);

    public:
        ~Service();
        void start() override;
        void stop() override;
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_SERVICE_H