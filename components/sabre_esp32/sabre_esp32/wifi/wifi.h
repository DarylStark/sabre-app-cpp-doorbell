#ifndef SABRE_ESP32_WIFI_H
#define SABRE_ESP32_WIFI_H

#include <bitset>
#include <esp_wifi.h>
#include <memory>

namespace sabre::esp32
{
    enum class WifiMode
    {
        STATION,
        SOFT_AP
    };

    class Wifi
    {
    private:
        Wifi();
        Wifi(const Wifi &) = delete;
        Wifi(Wifi &&) = delete;
        Wifi &operator=(const Wifi &) = delete;
        Wifi &operator=(Wifi &&) = delete;

        static std::shared_ptr<Wifi> _instance;

        bool _is_initialized = false;
        bool _wifi_started = false;

        wifi_init_config_t _wifi_init_config = WIFI_INIT_CONFIG_DEFAULT();

        std::bitset<2> _enabled_modes;

        void _set_mode_to_none();
        void _set_mode_to_both();
        void _set_mode_to_station();
        void _set_mode_to_soft_ap();
        void _set_mode();

    public:
        static std::shared_ptr<Wifi> get_instance();

        void init();

        void start();
        void stop(WifiMode mode);
        void deintialize();

        void add_mode(WifiMode mode);
        void remove_mode(WifiMode mode);

        void handle_event(esp_event_base_t event_base, int32_t event_id,
                          void *event_data);
    };
}; // namespace sabre::esp32

#endif // SABRE_ESP32_WIFI_H