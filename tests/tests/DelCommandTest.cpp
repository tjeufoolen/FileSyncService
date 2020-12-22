#include "DelCommandTest.h"

namespace Tests {
    DelCommandTest::DelCommandTest(asio::ip::tcp::iostream& server)
            :   Test{server, "DelCommandTest"} {}

    void DelCommandTest::RunTests()
    {
        TestFileDoesExist();
        TestSuccessful();
    }

    // Note: this test probably only runs successfully once, as the server contents will be updated.
    // This is totally normal, just undo the delete on the server side everytime you want to actually
    // test this feature.
    void DelCommandTest::TestSuccessful()
    {
        // arrange
        std::string expected { "OK" };
        std::string cmd { "del tjeu/delete-me.txt" };

        // act
        server_ << cmd << CRLF;
        std::string actual { GetLine() };

        // assert
        AssertEqual(expected == actual, "TestSuccessful");
    }

    void DelCommandTest::TestFileDoesExist()
    {
        // arrange
        std::string expected { "Error: no such file or directory" };
        std::string cmd { "del iets-met-een-hele-lange-naam-wat-zeker-niet-bestaat.txt" };

        // act
        server_ << cmd << CRLF;
        std::string actual { GetLine() };

        // assert
        AssertEqual(expected == actual, "TestFileDoesExist");
    }
}