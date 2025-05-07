#ifndef _SABRE_UART_OUTPUT_STREAM_BUFFER_H_
#define _SABRE_UART_OUTPUT_STREAM_BUFFER_H_

#include "./uart.h"
#include <streambuf>

namespace sabre
{
    class UARTStreamBuf : public std::streambuf
    {
        using int_type = std::streambuf::traits_type::int_type;

    public:
        UARTStreamBuf(sabre::UART &uart, size_t buffer_size = 512);
        ~UARTStreamBuf();

    protected:
        int_type overflow(int_type c) override;
        int sync() override;

    private:
        sabre::UART &_uart;
        char *_buffer;
        size_t _buffer_size;

        void _reset_put_buffer();
    };
} // namespace sabre

#endif // _SABRE_UART_OUTPUT_STREAM_BUFFER_H