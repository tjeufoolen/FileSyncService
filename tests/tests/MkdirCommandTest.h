#ifndef CPPLS2_TESTS_MKDIRCOMMANDTEST_H
#define CPPLS2_TESTS_MKDIRCOMMANDTEST_H

#include "Test.h"

namespace Tests {
    class MkdirCommandTest : public Test
    {
    public:
        MkdirCommandTest(asio::ip::tcp::iostream& server);
        void RunTests() override;
    private:
        void TestDirectoryDoesNotExist();
        void TestSuccessful();
    };
}

#endif //CPPLS2_TESTS_MKDIRCOMMANDTEST_H
