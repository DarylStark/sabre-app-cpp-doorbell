#include "freertos/FreeRTOS.h"
#include <cstring>
#include <iomanip>
#include <sabre/uart/uart_output_stream_buffer.h>
#include <sabre_esp32/esp32_factory.h>
#include <sabre_esp32/gpio/gpio.h>
#include <sabre_esp32/uart/uart.h>
#include <string>

#include <driver/gpio.h>

class Application
{
private:
    std::shared_ptr<sabre::Factory> _os_factory;

    // For output
    std::shared_ptr<sabre::UARTStreamBuf> _uart_stream_buf;
    std::shared_ptr<sabre::UARTStreamBuf> _uart_stream_buf_2;
    std::ostream _u0o;
    std::ostream _u2o;

    sabre::esp32::GPIO _led_gpio;
    sabre::esp32::GPIO _button;

public:
    Application(std::shared_ptr<sabre::Factory> factory)
        : _os_factory(factory), _u0o(nullptr), _u2o(nullptr), _led_gpio(2),
          _button(26)
    {
        // Configure output stream
        _uart_stream_buf =
            _os_factory->create_uart_output_stream_buffer(0, 115200, 1, 3, 8);
        _u0o.rdbuf(_uart_stream_buf.get());

        // Configure GPIOs
        _led_gpio.set_as_output();
        _led_gpio.set_low();
        _button.reset();
        _button.set_as_input();
        _button.enable_pullup();
        _button.set_inverse_level();

        gpio_dump_io_configuration(stdout, (1ULL << 26));
    }

    void run_loop()
    {
        _u0o << "\nBooted!!" << std::endl;
        while (true)
        {
            _led_gpio.set_level(_button.get_level());
            vTaskDelay(10 / portTICK_PERIOD_MS);
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