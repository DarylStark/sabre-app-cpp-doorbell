#include "./esp32_factory.h"

#include "./uart/uart.h"
#include <iostream>

namespace sabre::esp32
{
    std::ostream &
    ESP32Factory::create_uart_output_stream(uint16_t index,
                                            std::streambuf *buffer)
    {
        auto it = _output_streams.find(index);
        if (it == _output_streams.end())
            _output_streams[index] = std::make_unique<std::ostream>(buffer);
        if (buffer)
            _output_streams[index]->rdbuf(buffer);
        return *_output_streams[index];
    }
} // namespace sabre::esp32