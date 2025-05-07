#ifndef _SABRE_UART_H_
#define _SABRE_UART_H_

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