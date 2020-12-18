#include "Logger.h"

#include <iostream>

namespace Utils {
    const std::string Logger::LF = { "\n" };
    const std::string Logger::CRLF = { "\r\n" };
    const std::string Logger::PREFIX = { "dropbox>" };

    void Logger::inform(const std::string &message)
    {
        std::cout << message << LF << CRLF;
    }

    void Logger::error(const std::string &message)
    {
        std::cout << message << LF << CRLF;
    }
}