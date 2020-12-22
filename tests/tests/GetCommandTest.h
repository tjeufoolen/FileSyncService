#ifndef CPPLS2_TESTS_GETCOMMANDTEST_H
#define CPPLS2_TESTS_GETCOMMANDTEST_H

#include "Test.h"

namespace Tests {
    class GetCommandTest : public Test
    {
    public:
        GetCommandTest(asio::ip::tcp::iostream& server);
        void RunTests() override;
    private:
        void TestFileDoesNotExist();
    };
}

#endif //CPPLS2_TESTS_GETCOMMANDTEST_H
