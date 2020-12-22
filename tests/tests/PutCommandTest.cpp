#include "PutCommandTest.h"

#include <fstream>

namespace Tests {
    PutCommandTest::PutCommandTest(asio::ip::tcp::iostream &server)
            :   Test{server, "PutCommandTest"} {}

    void PutCommandTest::RunTests()
    {
        TestSuccessful();
        TestInvalidPath();
        TestNotEnoughDiskSpace();
    }

    void PutCommandTest::TestSuccessful()
    {
        // arrange
        std::string expected { "OK" };
        std::string path { std::string(BASE_DIRECTORY).append("tjeu/tjeu.txt") };
        auto size { std::filesystem::file_size(path) };
        std::string cmd { std::string("PUT tjeu/tjeu.txt ").append(std::to_string(size)) };

        // act
        // 1. send name and file size to server
        server_ << cmd << CRLF;
        // 2. send actual file contents
        std::ifstream file{ path, std::ios::in | std::ios::binary };
        std::unique_ptr<char[]> buffer { std::make_unique<char[]>(size) };
        file.read(buffer.get(), size);
        server_.write(buffer.get(), size);
        file.close();
        // 3. handle response
        std::string actual { GetLine() };

        // assert
        AssertEqual(expected.compare(actual), "TestSuccessful");
    }

    void PutCommandTest::TestInvalidPath()
    {
        // arrange
        std::string expected { "Error: invalid path" };
        std::string cmd { "PUT een-hele-lange-naam-zodat-we-zeker-weten-dat-deze-niet-bestaat/test.txt 0" };

        // act
        server_ << cmd << CRLF;
        std::string actual { GetLine() };

        // assert
        AssertEqual(expected.compare(actual), "TestInvalidPath");
    }

    void PutCommandTest::TestNotEnoughDiskSpace()
    {
        // arrange
        std::string expected { "Error: not enough disk space" };
        std::string cmd { std::string("PUT test.txt ").append(std::to_string(LLONG_MAX - 1)) };

        // act
        server_ << cmd << CRLF;
        std::string actual { GetLine() };

        // assert
        AssertEqual(expected.compare(actual), "TestNotEnoughDiskSpace");
    }
}