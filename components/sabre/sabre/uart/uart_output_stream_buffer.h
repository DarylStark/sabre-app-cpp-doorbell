#ifndef _SABRE_UART_OUTPUT_STREAM_BUFFER_H_
#define _SABRE_UART_OUTPUT_STREAM_BUFFER_H_

#include "./uart.h"
#include <memory>
#include <streambuf>

namespace sabre
{
    class UARTStreamBuf : public std::streambuf
    {
        using int_type = std::streambuf::traits_type::int_type;

    private:
        std::shared_ptr<sabre::UART> _uart;
        char *_buffer;
        size_t _buffer_size;

        void _reset_put_buffer();

    protected:
        int_type overflow(int_type c) override;
        int sync() override;

    public:
        UARTStreamBuf(std::shared_ptr<sabre::UART> uart,
                      size_t buffer_size = 512);
        ~UARTStreamBuf();
    };
} // namespace sabre

#endif // _SABRE_UART_OUTPUT_STREAM_BUFFER_H