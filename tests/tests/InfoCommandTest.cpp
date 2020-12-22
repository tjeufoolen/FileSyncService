#include "InfoCommandTest.h"

namespace Tests {
    InfoCommandTest::InfoCommandTest(asio::ip::tcp::iostream& server)
        :   Test{server, "InfoCommandTest"} {}

    void InfoCommandTest::RunTests()
    {
        TestResultEqual();
    }

    void InfoCommandTest::TestResultEqual()
    {
        // arrange
        std::string expected { "Dropbox server 1.0, copyright (c) 2021 Tjeu Foolen." };
        std::string cmd { "info" };

        // act
        server_ << cmd << CRLF;
        std::string actual { GetLine() };

        // assert
        AssertEqual(expected.compare(actual), "TestResultEqual");
    }
}