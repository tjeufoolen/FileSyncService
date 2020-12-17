#include "client.h"

#include <filesystem>
#include <iostream>

client::client(const std::string& hostname, const std::string& port, const std::string& baseDirectory)
    :   hostname{hostname},
        port{port},
        base_directory{std::filesystem::current_path().generic_string().append(baseDirectory)}
{
    connect();
}

void client::connect()
{
    server = std::make_unique<asio::ip::tcp::iostream>(hostname, port);
    if (!*server) throw std::runtime_error("could not connect to server");
}

void client::run()
{
    while (server.get()) {
        std::string resp;
        if (getline(*server, resp)) {
            resp.erase(resp.end() - 1); // remove '\r'
            std::cout << resp << lf;

            if (resp == "Bye.") {
                break;
            }

            std::cout << prompt;
            std::string req;

            if (getline(std::cin, req)) {
                *server << req << crlf;
            }
        }
    }
}