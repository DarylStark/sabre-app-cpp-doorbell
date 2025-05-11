#ifndef _SABRE_GPIO_H_
#define _SABRE_GPIO_H_

namespace sabre
{
    struct ISRConfig
    {
        void (*handler)(int);
        int gpio;
    };

    class GPIO
    {
    protected:
        bool _inverse_level = false;

    public:
        virtual void reset() = 0;
        virtual void set_as_output() = 0;
        virtual void set_as_input() = 0;

        // Output GPIOs
        virtual void set_high() = 0;
        virtual void set_low() = 0;
        virtual void set_level(bool level) = 0;

        // Input GPIOs
        virtual bool get_level() const = 0;
        virtual void set_inverse_level();
        virtual void set_original_level();
        virtual bool get_inverse_level() const;
        virtual void enable_pullup() = 0;
        virtual void enable_pulldown() = 0;
        virtual void disable_pullup() = 0;
        virtual void disable_pulldown() = 0;
        virtual void add_interrupt_handler(void (*handler)(int)) = 0;
    };
}; // namespace sabre

#endif // _SABRE_GPIO_H_