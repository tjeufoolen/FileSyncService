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
#include <filesystem>

std::vector<std::string> splitString(std::string& str, const char delim) {
    std::vector<std::string> out;

    // construct a stream from the string
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
        out.push_back(s);
    }

    return out;
}

int main() {
    try {
        const char* server_address{ "localhost" };
        const char* server_port{ "12345" };
        const char* prompt{ "avansync> " };
        const char* lf{ "\n" };
        const char* crlf{ "\r\n" };
        const std::string client_directory{std::string(std::filesystem::current_path()).append("/dropbox/")};

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
                    auto args = splitString(req, ' ');
                    if (args[0] == "put") {
                        auto client_path = std::string(client_directory).append(args[1]);

                        if (args.size() >= 2 && std::filesystem::exists(client_path)) {
                            auto size = std::filesystem::file_size(client_path);

                            server << "put " << args[1] << " " << std::to_string(size) << crlf;
                        } else {
                            std::cerr << "Error: invalid path" << crlf;
                        }
                    }

                    else {
                        server << req << crlf;
                    }
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
