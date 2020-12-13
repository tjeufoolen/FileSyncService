//
// server.cpp
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
        const int server_port{ 12345 };
        const char* lf{ "\n" };
        const char* crlf{ "\r\n" };

        asio::io_context io_context;
        asio::ip::tcp::acceptor server{ io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), server_port) };

        for (;;) {
            std::cerr << "waiting for client to connect\n";
            asio::ip::tcp::iostream client;
            server.accept(client.socket());
            std::cerr << "client connected from " << client.socket().local_endpoint() << lf;
            client << "Welcome to AvanSync server 1.0" << crlf;
            for (;;) {
                std::string request;
                getline(client, request);
                request.erase(request.end() - 1); // remove '\r'
                std::cerr << "client says: " << request << lf;

                if (request == "quit") {
                    client << "Bye." << crlf;
                    std::cerr << "will disconnect from client " << client.socket().local_endpoint() << lf;
                    break;
                }
                else {
                    client << request << crlf; // simply echo the request
                }
            }
        }

    }
    catch (const std::exception& ex) {
        std::cerr << "server: " << ex.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
