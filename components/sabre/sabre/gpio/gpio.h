#ifndef SABRE_GPIO_H
#define SABRE_GPIO_H

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

#endif // SABRE_GPIO_H