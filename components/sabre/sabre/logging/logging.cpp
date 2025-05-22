#include "logging.h"

namespace sabre
{
    LoggingLevel Logging::_level = LoggingLevel::NOTSET;

    Logger::Logger(const std::string &name) : _name(name) {}
    std::forward_list<std::shared_ptr<LogHandler>> Logging::_handlers;

    void Logger::log(const LoggingLevel level, const std::string &message)
    {
        Logging::log(level, _name, message);
    }

    void Logging::set_level(LoggingLevel level)
    {
        _level = level;
    }

    LoggingLevel Logging::get_level()
    {
        return _level;
    }

    void Logging::log(const LoggingLevel level, const std::string &logger_name,
                      const std::string &message)
    {
        if (level <= _level)
            for (const auto &handler : _handlers)
                handler->handle_log(level, logger_name, message);
    }

    void Logging::debug(const std::string &logger_name,
                        const std::string &message)
    {
        Logging::log(LoggingLevel::DEBUG, logger_name, message);
    }

    void Logging::info(const std::string &logger_name,
                       const std::string &message)
    {
        Logging::log(LoggingLevel::INFO, logger_name, message);
    }

    void Logging::notice(const std::string &logger_name,
                         const std::string &message)
    {
        Logging::log(LoggingLevel::NOTICE, logger_name, message);
    }

    void Logging::warning(const std::string &logger_name,
                          const std::string &message)
    {
        Logging::log(LoggingLevel::WARNING, logger_name, message);
    }

    void Logging::error(const std::string &logger_name,
                        const std::string &message)
    {
        Logging::log(LoggingLevel::ERROR, logger_name, message);
    }

    void Logging::critical(const std::string &logger_name,
                           const std::string &message)
    {
        Logging::log(LoggingLevel::CRITICAL, logger_name, message);
    }

    void Logging::alert(const std::string &logger_name,
                        const std::string &message)
    {
        Logging::log(LoggingLevel::ALERT, logger_name, message);
    }

    void Logging::emergency(const std::string &logger_name,
                            const std::string &message)
    {
        Logging::log(LoggingLevel::EMERGENCY, logger_name, message);
    }

    void Logging::add_handler(std::shared_ptr<LogHandler> handler)
    {
        _handlers.push_front(handler);
    }
} // namespace sabre