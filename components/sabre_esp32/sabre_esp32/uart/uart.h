#ifndef _SABRE_ESP32_UART_H_
#define _SABRE_ESP32_UART_H_

#include <cstddef> // For size_t
#include <cstdint> // For uint32_t

#include <driver/uart.h>
#include <sabre/uart/uart.h>

#define BUF_SIZE 1024

namespace sabre::esp32
{
    class UART : public sabre::UART
    {
    private:
        uart_port_t _port;
        int32_t _baud_rate;
        int _tx_pin;
        int _rx_pin;
        bool _is_initialized;

        void _initialize();

    public:
        UART(uart_port_t port, int32_t baud_rate, int tx_pin = 1,
             int rx_pin = 3);
        int write_byte(char data) const;
        void flush();

        int get_bytes(char *data, size_t length, uint32_t timeout = 1000) const;
    };
} // namespace sabre::esp32

#endif /* _SABRE_ESP32_UART_H_ */