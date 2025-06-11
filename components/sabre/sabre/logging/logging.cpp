#include "logging.h"

namespace sabre
{
    LoggingLevel Logging::_level = LoggingLevel::NOTSET;

    void Logger::log(const LoggingLevel level, const string &message)
    {
        Logging::log(level, _name, message);
    }

    void Logger::debug(const string &message)
    {
        log(LoggingLevel::DEBUG, message);
    }

    void Logger::info(const string &message)
    {
        log(LoggingLevel::INFO, message);
    }

    void Logger::notice(const string &message)
    {
        log(LoggingLevel::NOTICE, message);
    }

    void Logger::warning(const string &message)
    {
        log(LoggingLevel::WARNING, message);
    }

    void Logger::error(const string &message)
    {
        log(LoggingLevel::ERROR, message);
    }

    void Logger::critical(const string &message)
    {
        log(LoggingLevel::CRITICAL, message);
    }

    void Logger::alert(const string &message)
    {
        log(LoggingLevel::ALERT, message);
    }

    void Logger::emergency(const string &message)
    {
        log(LoggingLevel::EMERGENCY, message);
    }

    void Logging::set_level(LoggingLevel level)
    {
        _level = level;
    }

    LoggingLevel Logging::get_level()
    {
        return _level;
    }

    Logger::Logger(const string &name) : _name(name) {}
    std::forward_list<LogHandlerSharedPtr> Logging::_handlers;

    void Logging::log(const LoggingLevel level, const string &logger_name,
                      const string &message)
    {
        if (level <= _level)
            for (const auto &handler : _handlers)
                handler->handle_log(level, logger_name, message);
    }

    void Logging::add_handler(LogHandlerSharedPtr handler)
    {
        _handlers.push_front(handler);
    }
} // namespace sabre