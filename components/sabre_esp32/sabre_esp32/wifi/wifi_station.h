#ifndef SABRE_ESP32_WIFI_STATION_H
#define SABRE_ESP32_WIFI_STATION_H

#include "wifi.h"
#include <esp_wifi.h>
#include <sabre/logging/logging.h>
#include <sabre/wifi/wifi_station.h>
#include <string>

namespace sabre::esp32
{
    class WifiStation : public sabre::WifiStation
    {
    private:
        wifi_init_config_t _wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();
        wifi_config_t _wifi_config = {};
        std::shared_ptr<Wifi> _wifi_instance;

    protected:
        bool _wifi_started = false;
        bool _connected = false;
        bool _initialized = false;

        sabre::Logger _logger;

    public:
        WifiStation();
        void init() override;
        void connect(const std::string &ssid,
                     const std::string &password) override;
        void disconnect() override;
        void stop() override;
        void deinitialize() override;

        bool is_connected() const;

        // Handlers for the `main event loop`
        void wifi_event_handler(esp_event_base_t event_base, int32_t event_id,
                                void *event_data);
        void ip_event_handler(esp_event_base_t event_base, int32_t event_id,
                              void *event_data);
    };
    using WifiStationPtr = WifiStation *;
    using WifiStationSharedPtr = std::shared_ptr<WifiStation>;
} // namespace sabre::esp32

#endif // SABRE_ESP32_WIFI_STATION_H