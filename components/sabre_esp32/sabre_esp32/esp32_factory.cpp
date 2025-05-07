#include "./esp32_factory.h"

#include <iostream>

namespace sabre::esp32
{
    std::ostream &ESP32Factory::create_uart_output_stream(uint16_t uart_port)
    {
        auto it = _output_streams.find(uart_port);
        if (it == _output_streams.end())
            _output_streams[uart_port] =
                std::make_unique<std::ostream>(std::cout.rdbuf());
        return *_output_streams[uart_port];
    }
} // namespace sabre::esp32