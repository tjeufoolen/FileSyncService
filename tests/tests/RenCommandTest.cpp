#include "RenCommandTest.h"

#include <iostream>

namespace Tests {
    RenCommandTest::RenCommandTest(asio::ip::tcp::iostream &server)
        :   Test{server, "RenCommandTest"} {}

    void RenCommandTest::RunTests()
    {
        TestFileDoesNotExist();
        TestSuccessFullRename();
    }

    // Note: this test probably only runs successfully once, as the server contents will be updated.
    // This is totally normal, just undo the rename on the server side everytime you want to actually
    // test this feature.
    void RenCommandTest::TestSuccessFullRename()
    {
        // arrange
        std::string expected { "OK" };
        std::string cmd { "REN tjeu/rename-me.txt new-name.txt" };

        // act
        server_ << cmd << CRLF;
        std::string actual { GetLine() };

        // assert
        AssertEqual(expected == actual, "TestSuccessFullRename");
    }

    void RenCommandTest::TestFileDoesNotExist()
    {
        // arrange
        std::string expected { "Error: no such file or directory" };
        std::string cmd { "REN een-hele-lange-naam-die-zeker-niet-bestaat.txt new-name.txt" };

        // act
        server_ << cmd << CRLF;
        std::string actual { GetLine() };

        // assert
        AssertEqual(expected == actual, "TestFileDoesNotExist");
    }
}