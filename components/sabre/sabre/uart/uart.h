#ifndef SABRE_UART_H
#define SABRE_UART_H

#include <cstddef> // For size_t
#include <cstdint> // For uint32_t
#include <memory>

namespace sabre
{
    class UART
    {
    public:
        virtual int write_byte(char data) const = 0;
        virtual void flush() = 0;
    };
    using UARTPtr = UART *;
    using UARTSharedPtr = std::shared_ptr<UART>;
} // namespace sabre

#endif /* SABRE_UART_H */