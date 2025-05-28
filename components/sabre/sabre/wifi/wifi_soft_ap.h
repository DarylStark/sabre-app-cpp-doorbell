#ifndef SABRE_WIFI_SOFT_AP_H
#define SABRE_WIFI_SOFT_AP_H

namespace sabre
{
    class WifiSoftAP
    {
    public:
        virtual void init() = 0;
        virtual void start(std::string ssid, std::string password) = 0;
    };
}; // namespace sabre

#endif // SABRE_WIFI_SOFT_AP_H