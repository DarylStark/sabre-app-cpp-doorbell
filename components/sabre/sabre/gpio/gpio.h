#ifndef _SABRE_GPIO_H_
#define _SABRE_GPIO_H_

namespace sabre
{
    class GPIO
    {
    protected:
        bool _inverse_level = false;

    public:
        virtual void reset() = 0;
    };
}; // namespace sabre

#endif // _SABRE_GPIO_H_