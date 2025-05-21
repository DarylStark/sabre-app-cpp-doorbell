#ifndef SABRE_LOGGING_H
#define SABRE_LOGGING_H

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

    class Logging
    {
    private:
        static LoggingLevel _level;

    public:
        static void set_level(LoggingLevel level);
        static LoggingLevel get_level();
        static void log(const LoggingLevel level,
                        const std::string &logger_name,
                        const std::string &message);
        static void debug(const std::string &logger_name,
                          const std::string &message);
        static void info(const std::string &logger_name,
                         const std::string &message);
        static void notice(const std::string &logger_name,
                           const std::string &message);
        static void warning(const std::string &logger_name,
                            const std::string &message);
        static void error(const std::string &logger_name,
                          const std::string &message);
        static void critical(const std::string &logger_name,
                             const std::string &message);
        static void alert(const std::string &logger_name,
                              const std::string &message);
        static void emergency(const std::string &logger_name,
                              const std::string &message);
    };
}; // namespace sabre

#endif // SABRE_LOGGING_H