#include "DirCommandTest.h"

namespace Tests {
    DirCommandTest::DirCommandTest(asio::ip::tcp::iostream& server)
            :   Test{server, "DirCommandTest"} {}

    void DirCommandTest::RunTests()
    {
        TestDirectoryDoesNotExist();
    }

    void DirCommandTest::TestDirectoryDoesNotExist()
    {
        // arrange
        std::string expected { "Error: no such directory" };
        std::string cmd { "dir een-hele-lange-naam-zodat-we-zeker-weten-dat-deze-niet-bestaat" };

        // act
        server_ << cmd << CRLF;
        std::string actual { GetLine() };

        // assert
        AssertEqual(expected.compare(actual), "TestDirectoryDoesNotExist");
    }
}
