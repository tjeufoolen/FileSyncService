//
// client.cpp
//
// Created by Bob Polis at 2020-12-02
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <asio.hpp>

int main() {
    try {
        const char* server_address{ "localhost" };
        const char* server_port{ "12345" };
        const char* prompt{ "avansync> " };
        const char* lf{ "\n" };
        const char* crlf{ "\r\n" };

        asio::ip::tcp::iostream server{ server_address, server_port };
        if (!server) throw std::runtime_error("could not connect to server");

        while (server) {
            std::string resp;
            if (getline(server, resp)) {
                resp.erase(resp.end() - 1); // remove '\r'
                std::cout << resp << lf;
                if (resp == "Bye.") break;

                std::cout << prompt;
                std::string req;
                if (getline(std::cin, req)) {
                    server << req << crlf;
                }
            }
        }

    }
    catch (const std::exception& ex) {
        std::cerr << "client: " << ex.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
