#include "Logger.h"

#include <iostream>

namespace Utils {
    const std::string Logger::LF = { "\n" };
    const std::string Logger::CRLF = { "\r\n" };
    const std::string Logger::PREFIX = { "dropbox>" };

    void Logger::Inform(const std::string &message)
    {
        std::cout << message << CRLF;
    }

    void Logger::Error(const std::string &message)
    {
        std::cout << message << CRLF;
    }
}