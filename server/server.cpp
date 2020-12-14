//
// server.cpp
//
// Created by Bob Polis at 2020-12-02
//

#include <iostream>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <vector>
#include <filesystem>
#include <asio.hpp>

template <typename TP>
std::time_t to_time_t(TP tp) {
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()
                                                        + system_clock::now());
    return system_clock::to_time_t(sctp);
}

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
        const int server_port{ 12345 };
        const char* lf{ "\n" };
        const char* crlf{ "\r\n" };
        const std::string server_directory{std::string(std::filesystem::current_path()).append("/dropbox/")};

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

                auto args = splitString(request, ' ');

                // todo: refactor
                if (request == "info") {
                    client << "AvanSync server 1.0, copyright (c) 2020 Bob Polis." << crlf;
                    continue;
                }

                else if (args[0] == "dir") {
                    auto path = std::string(server_directory).append(args[1]);

                    // when no parameter specified or directory invalid
                    if (args.size() >= 2 && std::filesystem::exists(path)) {
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
                        continue;
                    } else {
                        client << "Error: no such directory" << crlf;
                        continue;
                    }
                }

                else if (args[0] == "put") {
                    // when no parameter specified or directory invalid
                    if (args.size() >= 3) {
                        auto file_path = std::string(server_directory).append(args[1]);
                        auto directory = std::filesystem::path(file_path).remove_filename();

                        if (std::filesystem::status(directory).permissions() != std::filesystem::perms::none) {
                            if (std::filesystem::space(directory).available >= stoi(args[2])) {
                                // todo: upload file
                                client << "OK" << crlf;
                                continue;
                            } else {
                                client << "Error: not enough disk space" << crlf;
                                continue;
                            }
                        } else {
                            client << "Error: no permission" << crlf;
                            continue;
                        }
                    }

                    continue;
                }

                if (args[0] == "del") {
                    auto path = std::string(server_directory).append(args[1]);

                    // when no parameter specified or directory invalid
                    if (args.size() >= 2 && std::filesystem::exists(path)) {
                        if (std::filesystem::status(path).permissions() != std::filesystem::perms::none) {
                            std::filesystem::remove_all(path);
                            client << "OK" << crlf;
                            continue;
                        } else {
                            client << "Error: no permission" << crlf;
                            continue;
                        }
                    } else {
                        client << "Error: no such file or directory" << crlf;
                        continue;
                    }
                }

                else if (args[0] == "mkdir") {
                    auto parent_dir = std::string(server_directory).append(args[1]);

                    // when no parameter specified
                    if (args.size() >= 3 && std::filesystem::exists(parent_dir)) {
                        auto& dirname = args[2];

                        if (std::filesystem::status(parent_dir).permissions() != std::filesystem::perms::none) {
                            std::filesystem::create_directory(parent_dir.append("/").append(dirname));
                            client << "OK" << crlf;
                            continue;
                        } else {
                            client << "Error: no permission" << crlf;
                            continue;
                        }
                    } else {
                        client << "Error: no such directory" << crlf;
                        continue;
                    }
                }

                else if (args[0] == "ren") {
                    auto path = std::string(server_directory).append(args[1]);

                    // when no parameter specified
                    if (args.size() >= 3 && std::filesystem::exists(path)) {
                        auto& name = args[2];

                        if (std::filesystem::status(path).permissions() != std::filesystem::perms::none) {
                            auto new_name = std::filesystem::path(path).remove_filename().append(name);
                            std::filesystem::rename(path, new_name);
                            client << "OK" << crlf;
                            continue;
                        } else {
                            client << "Error: no permission" << crlf;
                            continue;
                        }
                    } else {
                        client << "Error: no such file or directory" << crlf;
                        continue;
                    }
                }

                else if (request == "quit") {
                    client << "Bye." << crlf;
                    std::cerr << "will disconnect from client " << client.socket().local_endpoint() << lf;
                    break;
                }

                else {
                    client << request << crlf; // simply echo the request
                    continue;
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
