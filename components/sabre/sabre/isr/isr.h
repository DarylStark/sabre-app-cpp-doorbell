#ifndef _SABRE_ISR_H_
#define _SABRE_ISR_H_

#include "../gpio/gpio.h"

namespace sabre
{
    class ISR
    {
    public:
        virtual void set_handler(void (*handler)(int)) = 0;
    };
}; // namespace sabre

#endif // _SABRE_ISR_H_