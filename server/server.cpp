//
// server.cpp
//
// Created by Bob Polis at 2020-12-02
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <filesystem>
#include <asio.hpp>

template <typename TP>
std::time_t to_time_t(TP tp)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
                                                        + system_clock::now());
    return system_clock::to_time_t(sctp);
}

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

                // todo: refactor
                if (request == "info") {
                    client << "AvanSync server 1.0, copyright (c) 2020 Bob Polis." << crlf;
                }

                if (request.rfind("dir", 0) == 0) {
                    std::string path { request };
                    path.erase(0, 4); // remove 'dir ' from string

                    // when directory invalid or no parameter specified
                    if (std::filesystem::exists(path) && request.size() > 4) {
                        for (const auto & entry : std::filesystem::directory_iterator(path)) {
                            std::string type = (entry.is_directory() ? "D" : entry.is_regular_file() ? "F" : "*");
                            std::string name = entry.path().filename().string();

                            auto tp {entry.last_write_time()};
                            std::time_t tt {to_time_t(tp)};
                            std::tm* tm {std::gmtime(&tt)};
                            std::stringstream buffer;
                            buffer << std::put_time(tm, "%Y-%m-%d %H:%M:%S");
                            std::string updated_at {buffer.str()};

                            std::string size {std::to_string((entry.is_regular_file() ? entry.file_size() : 0))};

                            client << type << "|" << name << "|" << updated_at << "|" << size << crlf;
                        }
                    } else {
                        client << "Error: no such directory" << crlf;
                    }
                }

                else if (request == "quit") {
                    client << "Bye." << crlf;
                    std::cerr << "will disconnect from client " << client.socket().local_endpoint() << lf;
                    break;
                }

                else {
                    client << request << crlf; // simply echo the request
                }
                // todo: end refactor
            }
        }

    }
    catch (const std::exception& ex) {
        std::cerr << "server: " << ex.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
