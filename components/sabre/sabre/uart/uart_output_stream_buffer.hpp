#ifndef SABRE_UART_OUTPUT_STREAM_BUFFER_H
#define SABRE_UART_OUTPUT_STREAM_BUFFER_H

#include "uart.hpp"
#include <memory>
#include <streambuf>

namespace sabre
{
    class UARTStreamBuf : public std::streambuf
    {
        using int_type = std::streambuf::traits_type::int_type;

    private:
        UARTSharedPtr _uart;
        char *_buffer;
        size_t _buffer_size;

        void _reset_put_buffer();

    protected:
        int_type overflow(int_type c) override;
        int sync() override;

    public:
        UARTStreamBuf(UARTSharedPtr uart, size_t buffer_size = 512);
        ~UARTStreamBuf();
    };
    using UARTStreamBufPtr = UARTStreamBuf *;
    using UARTStreamBufSharedPtr = std::shared_ptr<UARTStreamBuf>;
} // namespace sabre

#endif // SABRE_UART_OUTPUT_STREAM_BUFFER_H