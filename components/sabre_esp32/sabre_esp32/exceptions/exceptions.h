#ifndef _SABRE_ESP32_EXCEPTIONS_H_
#define _SABRE_ESP32_EXCEPTIONS_H_

#include <sabre/exceptions/exceptions.h>

namespace sabre::esp32
{
    class ESP_IDF_Error : public sabre::APIError
    {
    public:
        ESP_IDF_Error(const std::string &s) : APIError(s) {}
    };

    inline void throw_if_esp_err(esp_err_t err, const std::string &msg)
    {
        if (err != ESP_OK)
            throw ESP_IDF_Error(msg);
    }

    inline void throw_if_negative_value(int32_t value, const std::string &msg)
    {
        if (value < 0)
            throw ESP_IDF_Error(msg);
    }
} // namespace sabre::esp32

#endif