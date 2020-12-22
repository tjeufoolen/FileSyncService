#ifndef CPPLS2_SERVER_LOGGER_H
#define CPPLS2_SERVER_LOGGER_H

#include <string>

namespace Utils {
    class Logger
    {
    public:
        static const std::string LF;
        static const std::string CRLF;
        static const std::string PREFIX;

        static void Inform(const std::string& message);
        static void Error(const std::string& message);
    };
}

#endif //CPPLS2_SERVER_LOGGER_H
