#ifndef SABRE_ESP32_CLIENTS_NTP_HPP
#define SABRE_ESP32_CLIENTS_NTP_HPP

#include <sabre/clients/ntp.hpp>
#include <string>

namespace sabre::esp32
{
    class NTPClient : public sabre::NTPClient
    {
    private:
        std::string _server;

    public:
        NTPClient(const std::string &server);
        void start();
        void stop();
        bool is_synchronized() const;
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_CLIENTS_NTP_HPP