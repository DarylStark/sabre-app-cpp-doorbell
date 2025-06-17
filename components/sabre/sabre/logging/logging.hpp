#ifndef SABRE_LOGGING_H
#define SABRE_LOGGING_H

#include <forward_list>
#include <memory>
#include <string>

namespace sabre
{
    enum class LoggingLevel : int
    {
        NOTSET = -1,
        EMERGENCY,
        ALERT,
        CRITICAL,
        ERROR,
        WARNING,
        NOTICE,
        INFO,
        DEBUG,
    };

    class Logger
    {
    private:
        std::string _name;

    public:
        Logger(const std::string &name);
        void log(const LoggingLevel level, const std::string &message);
        void debug(const std::string &message);
        void info(const std::string &message);
        void notice(const std::string &message);
        void warning(const std::string &message);
        void error(const std::string &message);
        void critical(const std::string &message);
        void alert(const std::string &message);
        void emergency(const std::string &message);
    };
    using LoggerPtr = Logger *;
    using LoggerSharedPtr = std::shared_ptr<Logger>;

    class LogHandler
    {
    public:
        virtual void handle_log(const LoggingLevel level,
                                const std::string &logger_name,
                                const std::string &message) = 0;
    };
    using LogHandlerPtr = LogHandler *;
    using LogHandlerSharedPtr = std::shared_ptr<LogHandler>;

    class Logging
    {
    private:
        static LoggingLevel _level;
        static std::forward_list<LogHandlerSharedPtr> _handlers;

    public:
        static void set_level(LoggingLevel level);
        static LoggingLevel get_level();
        static void log(const LoggingLevel level,
                        const std::string &logger_name,
                        const std::string &message);
        static void add_handler(LogHandlerSharedPtr handler);
    };
    using LoggingPtr = Logging *;
    using LoggingSharedPtr = std::shared_ptr<Logging>;
}; // namespace sabre

#endif // SABRE_LOGGING_H