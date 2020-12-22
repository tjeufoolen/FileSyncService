#ifndef CPPLS2_TESTS_PUTCOMMANDTEST_H
#define CPPLS2_TESTS_PUTCOMMANDTEST_H

#include "Test.h"

namespace Tests {
    class PutCommandTest : public Test
    {
    public:
        PutCommandTest(asio::ip::tcp::iostream& server);
        void RunTests() override;
    private:
        void TestSuccessful();
        void TestInvalidPath();
        void TestNotEnoughDiskSpace();
    };
}

#endif //CPPLS2_TESTS_PUTCOMMANDTEST_H
