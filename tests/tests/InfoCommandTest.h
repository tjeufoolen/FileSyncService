#ifndef CPPLS2_TESTS_INFOCOMMANDTEST_H
#define CPPLS2_TESTS_INFOCOMMANDTEST_H

#include "Test.h"

namespace Tests {
    class InfoCommandTest : public Test
    {
    public:
        InfoCommandTest(asio::ip::tcp::iostream& server);
        void RunTests() override;
    private:
        void TestResultEqual();
    };
}

#endif //CPPLS2_TESTS_INFOCOMMANDTEST_H
