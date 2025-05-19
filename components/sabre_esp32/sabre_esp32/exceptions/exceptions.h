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
} // namespace sabre::esp32

#endif