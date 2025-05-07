#ifndef _SABRE_FACTORY_H_
#define _SABRE_FACTORY_H_

#include <ostream>

namespace sabre
{
    class Factory
    {
    public:
        virtual std::ostream &
        create_uart_output_stream(uint16_t index,
                                  std::streambuf *buffer = nullptr) = 0;
    };

} // namespace sabre

#endif // _SABRE_FACTORY_H_