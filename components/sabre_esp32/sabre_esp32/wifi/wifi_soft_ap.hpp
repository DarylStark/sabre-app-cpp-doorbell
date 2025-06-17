#ifndef SABRE_ESP32_WIFI_SOFT_AP_H
#define SABRE_ESP32_WIFI_SOFT_AP_H

#include "wifi.hpp"
#include <esp_wifi.h>
#include <sabre/logging/logging.hpp>
#include <sabre/wifi/wifi_soft_ap.hpp>
#include <string>

namespace sabre::esp32
{
    class WifiSoftAP : public sabre::WifiSoftAP
    {
    private:
        wifi_init_config_t _wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
        wifi_config_t _wifi_config = {};
        std::shared_ptr<Wifi> _wifi_instance;

    protected:
        bool _wifi_started = false;
        sabre::Logger _logger;
        bool _initialized = false;

    public:
        WifiSoftAP();
        ~WifiSoftAP();
        void init();
        void start(std::string ssid, std::string password);
        void stop();
        void deinitialize();

        // Handlers for the `main event loop`
        void wifi_event_handler(esp_event_base_t event_base, int32_t event_id,
                                void *event_data);
    };
} // namespace sabre::esp32

#endif // SABRE_ESP32_WIFI_SOFT_AP_H