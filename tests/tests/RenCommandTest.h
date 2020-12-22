#ifndef CPPLS2_TESTS_RENCOMMANDTEST_H
#define CPPLS2_TESTS_RENCOMMANDTEST_H

#include "Test.h"

namespace Tests {
    class RenCommandTest : public Test
    {
    public:
        RenCommandTest(asio::ip::tcp::iostream& server);
        void RunTests() override;
    private:
        void TestSuccessFullRename();
        void TestFileDoesNotExist();
    };
}

#endif //CPPLS2_TESTS_RENCOMMANDTEST_H
