#include "GetCommandTest.h"

namespace Tests {
    GetCommandTest::GetCommandTest(asio::ip::tcp::iostream &server)
            :   Test{server, "GetCommandTest"} {}

    void GetCommandTest::RunTests()
    {
        TestFileDoesNotExist();
    }

    void GetCommandTest::TestFileDoesNotExist()
    {
        // arrange
        std::string expected { "Error: no such file" };
        std::string cmd { "GET een-hele-lange-naam-zodat-we-zeker-weten-dat-deze-niet-bestaat.txt" };

        // act
        server_ << cmd << CRLF;
        std::string actual { GetLine() };

        // assert
        AssertEqual(expected.compare(actual), "TestFileDoesNotExist");
    }
}