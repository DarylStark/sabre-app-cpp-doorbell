#ifndef _SABRE_ESP32_FACTORY_H_
#define _SABRE_ESP32_FACTORY_H_

#include <map>
#include <memory>
#include <sabre/os_factory.h>

namespace sabre::esp32
{
    class ESP32Factory : public sabre::Factory
    {
    private:
        std::map<uint16_t, std::unique_ptr<std::ostream>> _output_streams;

    public:
        std::ostream &
        create_uart_output_stream(uint16_t index,
                                  std::streambuf *buffer = nullptr) override;
    };
} // namespace sabre::esp32

#endif /* _SABRE_ESP32_FACTORY_H_ */