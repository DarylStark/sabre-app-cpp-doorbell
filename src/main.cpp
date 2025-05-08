#include "freertos/FreeRTOS.h"
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sabre/uart/uart_output_stream_buffer.h>
#include <sabre_esp32/esp32_factory.h>
#include <sabre_esp32/uart/uart.h>
#include <string>

class Application
{
private:
    std::shared_ptr<sabre::Factory> _os_factory;

    // For output
    std::shared_ptr<sabre::UARTStreamBuf> _uart_stream_buf;
    std::ostream _u0o;

public:
    Application(std::shared_ptr<sabre::Factory> factory)
        : _os_factory(factory), _u0o(nullptr)
    {
        _uart_stream_buf =
            _os_factory->create_uart_output_stream_buffer(0, 115200, 1, 3, 8);
        _u0o.rdbuf(_uart_stream_buf.get());
        _u0o << "\n\nHOI APP!" << std::endl;
    }

    void run_loop()
    {
        while (true)
        {
            _u0o << "123456789ABCDEF\n" << std::flush;
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
};

extern "C"
{
    void app_main(void)
    {
        Application app(std::make_shared<sabre::esp32::ESP32Factory>());
        app.run_loop();
        return;
    }
}