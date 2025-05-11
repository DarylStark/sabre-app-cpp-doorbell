#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>

#include <cstring>
#include <iomanip>
#include <sabre/uart/uart_output_stream_buffer.h>
#include <sabre_esp32/esp32_factory.h>
#include <sabre_esp32/gpio/gpio.h>
#include <sabre_esp32/gpio/input_gpio.h>
#include <sabre_esp32/gpio/output_gpio.h>
#include <sabre_esp32/uart/uart.h>
#include <string>

#include <driver/gpio.h>

QueueHandle_t interputQueue;

void very_special_isr_handler(int x)
{
    xQueueSendFromISR(interputQueue, new int(x), NULL);
}

void led_control_task(void *params)
{
    int pinNumber;
    while (true)
    {
        if (xQueueReceive(interputQueue, &pinNumber, portMAX_DELAY))
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

    sabre::esp32::OutputGPIO _led_gpio;
    sabre::esp32::InputGPIO _button;

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
        _led_gpio.set_low();
        _button.enable_pullup();
        _button.set_inverse_level();
        _button.add_interrupt_handler(very_special_isr_handler);

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
    void app_main(void)
    {
        interputQueue = xQueueCreate(10, sizeof(int));
        gpio_install_isr_service(0); // TODO: Move to Application class
        Application app(std::make_shared<sabre::esp32::ESP32Factory>());
        app.run_loop();

        return;
    }
}