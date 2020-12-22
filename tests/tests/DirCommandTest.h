#ifndef CPPLS2_TESTS_DIRCOMMANDTEST_H
#define CPPLS2_TESTS_DIRCOMMANDTEST_H

#include "Test.h"

namespace Tests {
    class DirCommandTest : public Test
    {
    public:
        DirCommandTest(asio::ip::tcp::iostream& server);
        void RunTests() override;
    private:
        void TestDirectoryDoesNotExist();
    };
}

#endif //CPPLS2_TESTS_DIRCOMMANDTEST_H
