#include "wifi_soft_ap.h"
#include <cstring>
#include <nvs_flash.h>

extern "C"
{
    void _wifi_event_handler_two(void *arg, esp_event_base_t event_base,
                                 int32_t event_id, void *event_data)
    {
        using sabre::esp32::WifiSoftAP;
        WifiSoftAP *obj = static_cast<WifiSoftAP *>(arg);
        obj->wifi_event_handler(event_base, event_id, event_data);
    }
}

namespace sabre::esp32
{
    WifiSoftAP::WifiSoftAP() : _logger("WifiSoftAP") {}

    void WifiSoftAP::wifi_event_handler(esp_event_base_t event_base,
                                        int32_t event_id, void *event_data)
    {
        if (event_id == WIFI_EVENT_AP_START)
        {
            _wifi_started = true;
            _logger.info("Service started");
        }
        else if (event_id == WIFI_EVENT_AP_STOP)
        {
            _wifi_started = false;
            _logger.info("Service stopped");
        }
        else if (event_id == WIFI_EVENT_AP_STACONNECTED)
        {
            _logger.info("Client connected");
        }
        else if (event_id == WIFI_EVENT_AP_STADISCONNECTED)
        {
            _logger.info("Client disconnected");
        }
    }

    void WifiSoftAP::init()
    {
        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
            ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
        {
            nvs_flash_erase();
            nvs_flash_init();
        }
        esp_netif_init();
        esp_event_loop_create_default();
        esp_netif_create_default_wifi_ap();

        esp_wifi_init(&_wifi_init_config);

        esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID,
                                   &_wifi_event_handler_two, this);
    }

    void WifiSoftAP::start(std::string ssid, std::string password)
    {
        std::strcpy((char *)_wifi_config.ap.ssid, ssid.c_str());
        std::strcpy((char *)_wifi_config.ap.password, password.c_str());
        _wifi_config.ap.channel = 1;
        _wifi_config.ap.max_connection = 4;
        _wifi_config.ap.authmode = WIFI_AUTH_WPA2_PSK;

        esp_wifi_set_mode(WIFI_MODE_AP);
        esp_wifi_set_config(WIFI_IF_AP, &_wifi_config);
        if (!_wifi_started)
            esp_wifi_start();
    }
} // namespace sabre::esp32