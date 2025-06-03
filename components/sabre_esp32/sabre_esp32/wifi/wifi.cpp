#include "wifi.h"
#include <esp_event.h>
#include <esp_netif.h>
#include <iostream>
#include <nvs_flash.h>

extern "C"
{
    void _esp32_wifi_event_handler(void *arg, esp_event_base_t event_base,
                                   int32_t event_id, void *event_data)
    {
        using sabre::esp32::Wifi;
        Wifi *obj = static_cast<Wifi *>(arg);
        obj->handle_event(event_base, event_id, event_data);
    }
}

namespace sabre::esp32
{
    std::shared_ptr<Wifi> Wifi::_instance = nullptr;

    Wifi::Wifi() {}

    void Wifi::_set_mode_to_none()
    {
        std::cout << "SETTING MODE TO NULL" << std::endl;
        esp_wifi_set_mode(WIFI_MODE_NULL);
    }

    void Wifi::_set_mode_to_both()
    {
        std::cout << "SETTING MODE TO BOTH" << std::endl;
        esp_wifi_set_mode(WIFI_MODE_APSTA);
    }

    void Wifi::_set_mode_to_station()
    {
        std::cout << "SETTING MODE TO STATION" << std::endl;
        esp_wifi_set_mode(WIFI_MODE_STA);
    }

    void Wifi::_set_mode_to_soft_ap()
    {
        std::cout << "SETTING MODE TO SOFTAP" << std::endl;
        esp_wifi_set_mode(WIFI_MODE_AP);
    }

    void Wifi::_set_mode()
    {
        if (_enabled_modes.none())
            _set_mode_to_none();
        else if (_enabled_modes.all())
            _set_mode_to_both();
        else if (_enabled_modes[static_cast<int>(WifiMode::STATION)] == 1)
            _set_mode_to_station();
        else if (_enabled_modes[static_cast<int>(WifiMode::SOFT_AP)] == 1)
            _set_mode_to_soft_ap();
    }

    std::shared_ptr<Wifi> Wifi::get_instance()
    {
        if (!_instance)
            _instance = std::shared_ptr<Wifi>(new Wifi());
        return _instance;
    }

    void Wifi::init()
    {
        if (_is_initialized)
            return;

        esp_err_t ret = nvs_flash_init();
        if (ret == ESP_ERR_NVS_NO_FREE_PAGES ||
            ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
        {
            nvs_flash_erase();
            nvs_flash_init();
        }
        esp_netif_init();
        esp_event_loop_create_default();
        esp_wifi_init(&_wifi_init_config);
        _is_initialized = true;

        esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_START,
                                   &_esp32_wifi_event_handler, this);
        esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_AP_START,
                                   &_esp32_wifi_event_handler, this);
        esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_STOP,
                                   &_esp32_wifi_event_handler, this);
        esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_AP_STOP,
                                   &_esp32_wifi_event_handler, this);
    }

    void Wifi::start()
    {
        if (_wifi_started)
            return;

        std::cout << "STARTING WIFI" << std::endl;
        esp_wifi_start();
        // TODO: Do we leave this in here?
        while (!_wifi_started)
            vTaskDelay(10 / portTICK_PERIOD_MS);
        std::cout << "STARTED" << std::endl;
    }

    void Wifi::deintialize()
    {
        if (_enabled_modes.any())
            return;

        esp_wifi_deinit();
        esp_netif_deinit();
    }

    void Wifi::add_mode(WifiMode mode)
    {
        _enabled_modes[static_cast<int>(mode)] = 1;
        _set_mode();
    }

    void Wifi::remove_mode(WifiMode mode)
    {
        _enabled_modes[static_cast<int>(mode)] = 0;
        _set_mode();
    }

    void Wifi::handle_event(esp_event_base_t event_base, int32_t event_id,
                            void *event_data)
    {
        if (event_id == WIFI_EVENT_STA_START || event_id == WIFI_EVENT_AP_START)
            _wifi_started = true;
        else if (event_id == WIFI_EVENT_STA_STOP ||
                 event_id == WIFI_EVENT_AP_STOP)
            _wifi_started = false;
    }
} // namespace sabre::esp32