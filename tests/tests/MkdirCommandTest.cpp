#include "MkdirCommandTest.h"

namespace Tests {
    MkdirCommandTest::MkdirCommandTest(asio::ip::tcp::iostream &server)
        :   Test{server, "MkdirCommandTest"} {}

    void MkdirCommandTest::RunTests()
    {
        TestDirectoryDoesNotExist();
        TestSuccessful();
    }

    void MkdirCommandTest::TestSuccessful()
    {
        // arrange
        std::string expected { "OK" };
        std::string cmd { "mkdir tjeu test-directory" };

        // act
        server_ << cmd << CRLF;
        std::string actual { GetLine() };

        // assert
        AssertEqual(expected == actual, "TestSuccessful");
    }

    void MkdirCommandTest::TestDirectoryDoesNotExist()
    {
        // arrange
        std::string expected { "Error: no such directory" };
        std::string cmd { "mkdir deze-hoofd-map-bestaat-niet-dat-weet-ik-zeker test-directory" };

        // act
        server_ << cmd << CRLF;
        std::string actual { GetLine() };

        // assert
        AssertEqual(expected == actual, "TestDirectoryDoesNotExist");
    }
}