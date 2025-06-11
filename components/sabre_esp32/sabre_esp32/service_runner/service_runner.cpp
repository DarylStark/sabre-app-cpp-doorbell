#include "service_runner.h"

namespace sabre::esp32
{
    void ServiceRunner::_runner(void *obj)
    {
        auto *_obj = static_cast<ServiceRunner *>(obj);
        _obj->_service();
        _obj->stop();
    }

    void ServiceRunner::start()
    {
        xTaskCreate(&ServiceRunner::_runner, "ServiceTask", 2048, this, 5,
                    &_freertos_handle);
        _is_running = true;
    }

    void ServiceRunner::stop()
    {
        if (_freertos_handle)
        {
            TaskHandle_t handle = _freertos_handle;
            _freertos_handle = nullptr;
            _is_running = false;
            vTaskDelete(handle);
        }
    }

    bool ServiceRunner::is_running() const
    {
        return _is_running;
    }
} // namespace sabre::esp32