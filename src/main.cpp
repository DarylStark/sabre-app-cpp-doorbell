#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>

#include <cstring>
#include <iomanip>
#include <sabre/uart/uart_output_stream_buffer.h>
#include <sabre_esp32/esp32_factory.h>
#include <sabre_esp32/gpio/input_gpio.h>
#include <sabre_esp32/gpio/output_gpio.h>
#include <sabre_esp32/uart/uart.h>
#include <string>

#include <driver/gpio.h>

#include <sabre_esp32/exceptions/exceptions.h>

#include <sabre/logging/logging.h>

#include <sabre/logging/log_handlers.h>

#include <iostream>

#include <sabre/generic/ipv4_address.h>
#include <sabre_esp32/wifi/wifi_station.h>

#include <sabre_esp32/wifi/wifi_soft_ap.h>

#include <sabre_esp32/utility/timed_waiter.h>

QueueHandle_t interruptQueue;

void very_special_isr_handler(int x)
{
    xQueueSendFromISR(interruptQueue, &x, NULL);
}

void led_control_task(void *params)
{
    int pinNumber;
    while (true)
    {
        if (xQueueReceive(interruptQueue, &pinNumber, portMAX_DELAY))
        {
            gpio_set_level(
                GPIO_NUM_2,
                gpio_get_level(static_cast<gpio_num_t>(pinNumber)) == 1 ? 0
                                                                        : 1);
        }
    }
}

class Application
{
private:
    std::shared_ptr<sabre::Factory> _os_factory;

    // Logging
    std::shared_ptr<sabre::Logger> _logger;

    // For output
    std::shared_ptr<sabre::UARTStreamBuf> _uart_stream_buf;
    std::shared_ptr<sabre::UARTStreamBuf> _uart_stream_buf_2;
    std::ostream _u0o;
    std::ostream _u2o;

    std::shared_ptr<sabre::OutputGPIO> _led_gpio;
    std::shared_ptr<sabre::InputGPIO> _button;

    std::shared_ptr<sabre::WifiStation> _wifi_station;

    std::shared_ptr<sabre::WifiSoftAP> _wifi_soft_ap;

protected:
    std::shared_ptr<sabre::OutputGPIO> _get_led_gpio() const
    {
        std::shared_ptr<sabre::OutputGPIO> gpio =
            _os_factory->create_output_gpio(2);
        return gpio;
    }

    std::shared_ptr<sabre::InputGPIO> _get_button_gpio() const
    {
        std::shared_ptr<sabre::InputGPIO> gpio =
            _os_factory->create_input_gpio(26);
        gpio->enable_pullup();
        gpio->set_inverse_level();
        gpio->add_interrupt_handler(very_special_isr_handler,
                                    sabre::ISRTrigger::BOTH);
        return gpio;
    }

public:
    Application(std::shared_ptr<sabre::Factory> factory)
        : _os_factory(factory), _u0o(nullptr), _u2o(nullptr)
    {
        // Wait a bit to make sure the bootloader logging is done
        vTaskDelay(100 / portTICK_PERIOD_MS);

        // Configure output stream
        _uart_stream_buf =
            _os_factory->create_uart_output_stream_buffer(0, 115200, 1, 3, 8);
        _u0o.rdbuf(_uart_stream_buf.get());

        // Configure logging
        auto ostream_log_handler =
            std::make_shared<sabre::OStreamLogHandler>(_u0o);
        _logger = std::make_shared<sabre::Logger>("APP");
        sabre::Logging::set_level(sabre::LoggingLevel::DEBUG);
        sabre::Logging::add_handler(ostream_log_handler);

        _logger->info("Starting application...");

        // Configure WiFi
        _u0o << "Starting AP mode" << std::endl;
        _wifi_soft_ap = _os_factory->create_wifi_soft_ap();
        _wifi_soft_ap->init();
        _wifi_soft_ap->start("ESP32-test", "testtest");

        vTaskDelay(5000 / portTICK_PERIOD_MS);

        _u0o << "Starting station mode" << std::endl;
        _wifi_station = _os_factory->create_wifi_station();
        _wifi_station->init();
        _wifi_station->connect("SSID", "PASSWORD");

        vTaskDelay(5000 / portTICK_PERIOD_MS);
        _u0o << "Stopping station mode" << std::endl;
        _wifi_station->stop();

        vTaskDelay(5000 / portTICK_PERIOD_MS);
        _u0o << "Stopping AP mode" << std::endl;
        _wifi_soft_ap->stop();

        // Configure GPIOs
        _led_gpio = _get_led_gpio();
        _button = _get_button_gpio();

        // Create FreeRTOS tasks
        xTaskCreate(led_control_task, "LED_Control_Task", 2048, NULL, 1, NULL);

        _logger->info("Bootup done.");
    }

    void run_loop()
    {
        _logger->info("Starting loop");
        while (true)
            vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
};

extern "C"
{
    void app_main(void)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        std::cout << "Starting!\n";
        int a = 0;
        sabre::esp32::TimedWaiter x([&a]() { return a++ == 100; }, 1001, 10);
        std::cout << "Starting!\n";

        if (x())
            std::cout << "Success in " << x.get_result_runtime() << " ms\n";
        else
            std::cout << "Failed in " << x.get_result_runtime() << " ms\n";

        std::cout << "Done!\n";
        std::endl(std::cout);

        return;

        interruptQueue = xQueueCreate(10, sizeof(int));
        gpio_install_isr_service(0); // TODO: Move to Application class
        Application app(std::make_shared<sabre::esp32::ESP32Factory>());
        app.run_loop();

        return;
    }
}