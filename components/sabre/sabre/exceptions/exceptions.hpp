#ifndef SABRE_EXCEPTIONS_H
#define SABRE_EXCEPTIONS_H

#include <stdexcept>
#include <string>

namespace sabre
{
    class SabreException : public std::runtime_error
    {
    public:
        explicit SabreException(const std::string &message)
            : std::runtime_error(message)
        {
        }
    };

    class APIError : public SabreException
    {
    protected:
        APIError(const std::string &msg) : SabreException(msg) {}

    public:
        APIError() : SabreException("Unknown API error") {}
    };
} // namespace sabre

#endif // SABRE_EXCEPTIONS_H