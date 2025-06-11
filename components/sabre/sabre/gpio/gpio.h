#ifndef SABRE_GPIO_H
#define SABRE_GPIO_H

#include <memory>

namespace sabre
{
    class GPIO
    {
    protected:
        bool _inverse_level = false;

    public:
        virtual void reset() = 0;
    };
    using GPIOOPtr = GPIO *;
    using GPIOOSharedPtr = std::shared_ptr<GPIO>;
}; // namespace sabre

#endif // SABRE_GPIO_H