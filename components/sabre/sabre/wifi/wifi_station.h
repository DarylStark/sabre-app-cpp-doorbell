#ifndef SABRE_WIFI_STATION_H
#define SABRE_WIFI_STATION_H

#include <string>

namespace sabre
{
    class WifiStation
    {
    public:
        virtual void init() = 0;
        virtual void connect(const std::string &ssid,
                             const std::string &password) = 0;
        virtual void disconnect() = 0;
        virtual void stop() = 0;
        virtual void deinitialize() = 0;

        virtual bool is_connected() const = 0;
    };
} // namespace sabre

#endif // SABRE_WIFI_STATION_H