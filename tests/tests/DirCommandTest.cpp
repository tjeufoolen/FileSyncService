#include "DirCommandTest.h"

#include <iostream>

#include "StringSplitter.h"

namespace Tests {
    DirCommandTest::DirCommandTest(asio::ip::tcp::iostream& server)
            :   Test{server, "DirCommandTest"} {}

    void DirCommandTest::RunTests()
    {
        TestDirectoryDoesNotExist();
        TestSuccessful();
    }

    void DirCommandTest::TestSuccessful()
    {
        // arrange
        std::string cmd { "dir ." };

        // act
        server_ << cmd << CRLF;

        // first response is amount of lines
        try {
            int lines{stoi(GetLine())};

            for (int i = 0; i < lines; i++) {
                std::string line { GetLine() };
                std::vector parts { *std::move(StringSplitter::Split(line, '|')) };

                if (parts.size() == 4) {
                    std::string& type { parts[0] };
                    if (type == "F" || type == "D" || type == "*") {
                        AssertEqual(true, "TestSuccessful");
                        continue;
                    }
                }

                AssertEqual(false, "TestSuccessful");
            }
        } catch (const std::invalid_argument&) {
            AssertEqual(false, "TestSuccessful");
        }
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
        AssertEqual(expected == actual, "TestDirectoryDoesNotExist");
    }
}
