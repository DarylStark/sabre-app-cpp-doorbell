#ifndef _SABRE_EXCEPTIONS_H_
#define _SABRE_EXCEPTIONS_H_

#include <exception>
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

#endif // _SABRE_EXCEPTIONS_H_