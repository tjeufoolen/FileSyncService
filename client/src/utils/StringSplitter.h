#ifndef CPPLS2_CLIENT_STRINGSPLITTER_H
#define CPPLS2_CLIENT_STRINGSPLITTER_H

#include <string>
#include <vector>
#include <memory>

namespace Utils {
    struct StringSplitter
    {
        static std::unique_ptr<std::vector<std::string>> Split(const std::string& str, char delimiter);
    };
}

#endif //CPPLS2_CLIENT_STRINGSPLITTER_H
