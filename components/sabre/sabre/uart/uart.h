#ifndef SABRE_UART_H
#define SABRE_UART_H

#include <cstddef> // For size_t
#include <cstdint> // For uint32_t

namespace sabre
{
    class UART
    {
    public:
        virtual int write_byte(char data) const = 0;
        virtual void flush() = 0;
    };
} // namespace sabre

#endif /* SABRE_UART_H */