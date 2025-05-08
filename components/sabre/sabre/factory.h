#ifndef _SABRE_FACTORY_H_
#define _SABRE_FACTORY_H_

#include "./uart/uart.h"
#include "./uart/uart_output_stream_buffer.h"
#include <memory>
#include <ostream>

namespace sabre
{
    class Factory
    {
    public:
        virtual std::shared_ptr<sabre::UART>
        create_uart_object(uint32_t uart_number, int32_t baud_rate,
                           int32_t tx_pin, int32_t rx_pin) const = 0;

        virtual std::shared_ptr<sabre::UARTStreamBuf>
        create_uart_output_stream_buffer(uint32_t uart_number,
                                         int32_t baud_rate, int32_t tx_pin,
                                         int32_t rx_pin,
                                         size_t buffer_size) const;
    };

} // namespace sabre

#endif // _SABRE_FACTORY_H_