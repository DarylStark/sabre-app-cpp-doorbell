#ifndef _SABRE_FACTORY_H_
#define _SABRE_FACTORY_H_

#include "./uart/uart.h"
#include "./uart/uart_output_stream_buffer.h"
#include "gpio/input_gpio.h"
#include "gpio/output_gpio.h"
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

        virtual std::shared_ptr<InputGPIO>
        create_input_gpio(int32_t pin) const = 0;

        virtual std::shared_ptr<OutputGPIO>
        create_output_gpio(int32_t pin) const = 0;
    };

} // namespace sabre

#endif // _SABRE_FACTORY_H_