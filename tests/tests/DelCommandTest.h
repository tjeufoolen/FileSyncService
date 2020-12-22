#ifndef CPPLS2_TESTS_DELCOMMANDTEST_H
#define CPPLS2_TESTS_DELCOMMANDTEST_H

#include "Test.h"

namespace Tests {
    class DelCommandTest : public Test
    {
    public:
        DelCommandTest(asio::ip::tcp::iostream& server);
        void RunTests() override;
    private:
        void TestFileDoesExist();
        void TestSuccessful();
    };
}

#endif //CPPLS2_TESTS_DELCOMMANDTEST_H
