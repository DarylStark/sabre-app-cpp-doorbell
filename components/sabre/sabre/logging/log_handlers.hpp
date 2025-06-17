#ifndef SABRE_LOG_HANDLERS_H
#define SABRE_LOG_HANDLERS_H

#include "logging.hpp"
#include <memory>
#include <ostream>
#include <vector>

namespace sabre
{
    class OStreamLogHandler : public LogHandler
    {
    private:
        std::ostream &_stream;

    public:
        OStreamLogHandler(std::ostream &stream);
        void handle_log(const LoggingLevel level,
                        const std::string &logger_name,
                        const std::string &message) override;
    };
    using OStreamLogHandlerPtr = OStreamLogHandler *;
    using OStreamLogHandlerSharedPtr = std::shared_ptr<OStreamLogHandler>;

    class LogBufferHandler : public LogHandler
    {
    private:
        std::vector<std::string> _buffer;
        size_t _max_size;

    public:
        LogBufferHandler(size_t size);
        void handle_log(const LoggingLevel level,
                        const std::string &logger_name,
                        const std::string &message) override;
        const std::vector<std::string> &get_buffer() const;
    };
    using LogBufferHandlerPtr = LogBufferHandler *;
    using LogBufferHandlerSharedPtr = std::shared_ptr<LogBufferHandler>;
} // namespace sabre

#endif // SABRE_LOG_HANDLERS_H