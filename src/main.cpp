#include "freertos/FreeRTOS.h"
#include <cstring>
#include <iomanip>
#include <iostream>
#include <sabre/uart/uart_output_stream_buffer.h>
#include <sabre_esp32/esp32_factory.h>
#include <sabre_esp32/uart/uart.h>
#include <string>

extern "C"
{
    void app_main(void)
    {
        sabre::esp32::UART uart(UART_NUM_0, 115200);
        sabre::UARTStreamBuf uart_streambuf(uart);
        // std::ostream uart_stream(&uart_streambuf);

        sabre::esp32::ESP32Factory factory;
        std::ostream &uart_stream =
            factory.create_uart_output_stream(0, &uart_streambuf);
        std::ostream &uart_stream2 = factory.create_uart_output_stream(0);

        uint64_t counter = 0;
        while (true)
        {
            vTaskDelay(100 / portTICK_PERIOD_MS);
            uart_stream << "Counter value: " << counter << '\n' << std::flush;
            counter++;
        }
        return;
    }
}