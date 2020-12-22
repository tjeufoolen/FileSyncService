#ifndef CPPLS2_TESTS_STRINGSPLITTER_H
#define CPPLS2_TESTS_STRINGSPLITTER_H

#include <string>
#include <vector>
#include <memory>

struct StringSplitter
{
    static std::unique_ptr<std::vector<std::string>> Split(const std::string& str, char delimiter);
};

#endif //CPPLS2_TESTS_STRINGSPLITTER_H
