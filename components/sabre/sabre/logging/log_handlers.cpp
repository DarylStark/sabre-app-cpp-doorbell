#include "log_handlers.h"

namespace sabre
{
    OStreamLogHandler::OStreamLogHandler(std::ostream &stream) : _stream(stream)
    {
    }

    void OStreamLogHandler::handle_log(const LoggingLevel level,
                                       const std::string &logger_name,
                                       const std::string &message)
    {
        _stream << "[" << logger_name << "] - " << static_cast<int>(level)
                << " - " << message << std::endl;
    }

    LogBufferHandler::LogBufferHandler(size_t size)
        : _buffer(0), _max_size(size)
    {
        _buffer.reserve(size);
    }

    void LogBufferHandler::handle_log(const LoggingLevel level,
                                      const std::string &logger_name,
                                      const std::string &message)
    {
        _buffer.push_back("[" + logger_name + "] " + message);
        if (_buffer.size() > _max_size)
            _buffer.erase(_buffer.begin());
    }

    const std::vector<std::string> &LogBufferHandler::get_buffer() const
    {
        return _buffer;
    }
} // namespace sabre