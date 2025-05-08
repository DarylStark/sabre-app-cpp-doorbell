#ifndef _SABRE_GPIO_H_
#define _SABRE_GPIO_H_

namespace sabre
{
    class GPIO
    {
    public:
        virtual void reset() = 0;
        virtual void set_high() = 0;
        virtual void set_low() = 0;
    };
}; // namespace sabre

#endif // _SABRE_GPIO_H_