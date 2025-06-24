#ifndef SABRE_CLIENTS_NTP_HPP
#define SABRE_CLIENTS_NTP_HPP

#include <string>

namespace sabre
{
    class NTPClient
    {
    public:
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual bool is_synchronized() const = 0;
    };
} // namespace sabre

#endif // SABRE_CLIENTS_NTP_HPP