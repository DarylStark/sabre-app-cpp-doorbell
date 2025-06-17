#include "service_runner.hpp"

namespace sabre
{
    void ServiceRunner::operator()()
    {
        start();
    }
}; // namespace sabre