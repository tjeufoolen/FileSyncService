#include <asio.hpp>
#include <iostream>

#include "tests/Tests.h"

const std::string CRLF = { "\r\n" };
std::unique_ptr<asio::ip::tcp::iostream> server_;

void Connect() {
    if (server_ == nullptr) {
        server_ = std::make_unique<asio::ip::tcp::iostream>("localhost", "12345");
        if (!*server_) throw std::runtime_error("could not Connect to server");

        // get welcome message
        std::string str;
        getline(*server_, str);
    }
}

void Disconnect() {
    *server_ << "quit" << "\r\n";
}

int main()
{
    Connect();

    // tests
    Tests::InfoCommandTest{*server_}.RunTests();
    Tests::DirCommandTest{*server_}.RunTests();
    Tests::GetCommandTest{*server_}.RunTests();
    Tests::PutCommandTest{*server_}.RunTests();

    Disconnect();
}