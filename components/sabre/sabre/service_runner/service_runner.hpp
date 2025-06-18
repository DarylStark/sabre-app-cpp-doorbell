#ifndef SABRE_SERVICE_RUNNER_H
#define SABRE_SERVICE_RUNNER_H

#include <memory>

namespace sabre
{
    class ServiceRunner
    {
    protected:
        virtual void _service() = 0;

    public:
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual bool is_running() const = 0;

        virtual void operator()();
    };
    using ServiceRunnerPtr = ServiceRunner *;
    using ServiceRunnerSharedPtr = std::shared_ptr<ServiceRunner>;
} // namespace sabre

#endif // SABRE_SERVICE_RUNNER_H