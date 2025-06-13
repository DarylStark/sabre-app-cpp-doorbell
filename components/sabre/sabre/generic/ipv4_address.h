#ifndef SABRE_IPV4_ADDRESS_H
#define SABRE_IPV4_ADDRESS_H

#include <cstdint>
#include <memory>
#include <string>

namespace sabre
{
    class IPv4Address
    {
        uint32_t _address;

    public:
        IPv4Address();
        IPv4Address(uint32_t address);

        void set(uint32_t address);

        uint16_t operator[](uint8_t octet) const;
        operator uint32_t() const;
        operator std::string() const;
    };
    using IPv4AddressPtr = IPv4Address *;
    using IPv4AddressSharedPtr = std::shared_ptr<IPv4Address>;
}; // namespace sabre

#endif // SABRE_IPV4_ADDRESS_H