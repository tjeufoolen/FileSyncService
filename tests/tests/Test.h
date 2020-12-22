#ifndef CPPLS2_TESTS_TEST_H
#define CPPLS2_TESTS_TEST_H

#include <asio.hpp>
#include <memory>
#include <string>
#include <filesystem>

namespace Tests {
    class Test
    {
        std::string name_;
    public:
        Test(asio::ip::tcp::iostream& server, const std::string& name);
        virtual void RunTests() = 0;
    protected:
        const std::string CRLF = { "\r\n" };
        const std::string BASE_DIRECTORY = {std::filesystem::current_path().generic_string().append("/dropbox/")};
        asio::ip::tcp::iostream& server_;

        std::string GetLine();
        void AssertEqual(bool equal, const std::string& methodName="");
    };

}
#endif //CPPLS2_TESTS_TEST_H
