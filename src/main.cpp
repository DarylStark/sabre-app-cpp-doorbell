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

#include <iostream>

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

    // For output
    std::shared_ptr<sabre::UARTStreamBuf> _uart_stream_buf;
    std::shared_ptr<sabre::UARTStreamBuf> _uart_stream_buf_2;
    std::ostream _u0o;
    std::ostream _u2o;

    std::shared_ptr<sabre::OutputGPIO> _led_gpio;
    std::shared_ptr<sabre::InputGPIO> _button;

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
        // Configure output stream
        _uart_stream_buf =
            _os_factory->create_uart_output_stream_buffer(0, 115200, 1, 3, 8);
        _u0o.rdbuf(_uart_stream_buf.get());

        _led_gpio = _get_led_gpio();
        _button = _get_button_gpio();

        xTaskCreate(led_control_task, "LED_Control_Task", 2048, NULL, 1, NULL);
    }

    void run_loop()
    {
        _u0o << "\nBooted!!" << std::endl;
        while (true)
            vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
};

extern "C"
{
    // void app_main(void)
    // {
    //     interruptQueue = xQueueCreate(10, sizeof(int));
    //     gpio_install_isr_service(0); // TODO: Move to Application class
    //     Application app(std::make_shared<sabre::esp32::ESP32Factory>());
    //     app.run_loop();

    //     return;
    // }

    class OStreamLogHandler : public sabre::LogHandler
    {
    private:
        std::ostream &_stream;

    public:
        OStreamLogHandler(std::ostream &stream) : _stream(stream) {}
        void handle_log(const sabre::LoggingLevel level,
                        const std::string &logger_name,
                        const std::string &message) override
        {
            _stream << "HANDLER: [" << logger_name << "] " << message
                    << std::endl;
        }
    };

    class LogBufferHandler : public sabre::LogHandler
    {
    private:
        std::vector<std::string> _buffer;
        size_t _max_size;

    public:
        LogBufferHandler(size_t size) : _buffer(0), _max_size(size)
        {
            _buffer.reserve(size);
        }

        void handle_log(const sabre::LoggingLevel level,
                        const std::string &logger_name,
                        const std::string &message) override
        {
            _buffer.push_back("[" + logger_name + "] " + message);
            if (_buffer.size() > _max_size)
                _buffer.erase(_buffer.begin());
        }

        const std::vector<std::string> &get_buffer() const
        {
            return _buffer;
        }
    };

    void app_main(void)
    {
        using namespace sabre;

        std::shared_ptr<LogBufferHandler> log_buffer_handler =
            std::make_shared<LogBufferHandler>(8);

        Logging::set_level(LoggingLevel::DEBUG);
        Logging::add_handler(std::make_shared<OStreamLogHandler>(std::cout));
        Logging::add_handler(log_buffer_handler);

        Logger logger = sabre::Logger("app_main");
        Logger logger2 = sabre::Logger("APP");

        logger.log(LoggingLevel::DEBUG, "Debug message");
        logger2.log(LoggingLevel::EMERGENCY, "Emergency message");
        logger.log(LoggingLevel::INFO, "Log handler 1");
        logger2.log(LoggingLevel::INFO, "Log handler 2");
        logger.log(LoggingLevel::INFO, "Log handler 3");
        logger2.log(LoggingLevel::INFO, "Log handler 4");
        logger.log(LoggingLevel::INFO, "Log handler 5");
        logger2.log(LoggingLevel::INFO, "Log handler 6");
        logger.log(LoggingLevel::INFO, "Log handler 7");
        logger2.log(LoggingLevel::INFO, "Log handler 8");
        logger.log(LoggingLevel::INFO, "Log handler 9");
        logger2.log(LoggingLevel::INFO, "Log handler 10");
        logger.log(LoggingLevel::INFO, "Log handler 11");
        logger2.log(LoggingLevel::INFO, "Log handler 12");
        logger.log(LoggingLevel::INFO, "Log handler 13");

        std::endl(std::cout);

        for (const auto &log_message : log_buffer_handler->get_buffer())
            std::cout << "BUFFER: " << log_message << std::endl;
    }
}