#include "StringSplitter.h"

#include <sstream>

namespace Utils {
    std::unique_ptr<std::vector<std::string>> StringSplitter::Split(const std::string &str, char delimiter)
    {
        std::unique_ptr<std::vector<std::string>> out { std::make_unique<std::vector<std::string>>() };
        std::stringstream ss(str);
        std::string s;

        while (std::getline(ss, s, delimiter)) {
            out->emplace_back(s);
        }

        return out;
    }
}