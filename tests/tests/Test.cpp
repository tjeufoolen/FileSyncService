#include "Test.h"

#include <iostream>

namespace Tests {
    Test::Test(asio::ip::tcp::iostream& server, const std::string& name)
        :  name_{name}, server_{server} {}

    std::string Test::GetLine()
    {
        std::string str;
        getline(server_, str);
        return str;
    }

    void Test::AssertEqual(bool equal, const std::string& methodName)
    {
        std::string result{ equal ? "[OK]" : "[ERROR]" };
        std::string prefix{ name_ };
        std::string suffix{ methodName.empty() ? "" : std::string( " -> ").append(methodName) };

        std::cout << result << " " << prefix << suffix << CRLF;
    }
}