#ifndef SABRE_LOGGING_H
#define SABRE_LOGGING_H

#include <forward_list>
#include <memory>
#include <string>

using std::string;

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
        string _name;

    public:
        Logger(const string &name);
        void log(const LoggingLevel level, const string &message);
        void debug(const string &message);
        void info(const string &message);
        void notice(const string &message);
        void warning(const string &message);
        void error(const string &message);
        void critical(const string &message);
        void alert(const string &message);
        void emergency(const string &message);
    };
    using LoggerPtr = Logger *;
    using LoggerSharedPtr = std::shared_ptr<Logger>;

    class LogHandler
    {
    public:
        virtual void handle_log(const LoggingLevel level,
                                const string &logger_name,
                                const string &message) = 0;
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
        static void log(const LoggingLevel level, const string &logger_name,
                        const string &message);
        static void add_handler(LogHandlerSharedPtr handler);
    };
    using LoggingPtr = Logging *;
    using LoggingSharedPtr = std::shared_ptr<Logging>;
}; // namespace sabre

#endif // SABRE_LOGGING_H