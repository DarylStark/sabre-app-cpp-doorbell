#ifndef SABRE_SERVICE_H
#define SABRE_SERVICE_H

#include <functional>
#include <memory>

namespace sabre
{
    using ServiceHandler = std::function<void(void)>;
    class Service
    {
    protected:
        ServiceHandler _fn;

    public:
        Service(ServiceHandler function);
        virtual void start() = 0;
        virtual void stop() = 0;
    };
    using ServicePtr = Service *;
    using ServiceSharedPtr = std::shared_ptr<Service>;
} // namespace sabre

#endif // SABRE_SERVICE_H