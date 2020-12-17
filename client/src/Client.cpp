#include "Client.h"

#include <filesystem>
#include <iostream>

#include "Logger.h"
#include "EndSessionException.h"

Client::Client(const std::string& hostname, const std::string& port, const std::string& baseDirectory)
    : HOSTNAME{hostname},
      PORT{port},
      BASE_DIRECTORY{std::filesystem::current_path().generic_string().append(baseDirectory)}
{
    connect();
}

void Client::connect()
{
    server_ = std::make_unique<asio::ip::tcp::iostream>(HOSTNAME, PORT);
    if (!*server_) throw std::runtime_error("could not connect to server");
}

void Client::run()
{
    bool keepRunning{true};
    while (server_.get() && keepRunning) {
        std::string resp;

        if (getline(*server_, resp)) {
            resp.erase(resp.end() - 1); // remove '\r'

            handleResponse(resp);

            std::cout << Utils::Logger::PREFIX;
            std::string req;

            if (getline(std::cin, req)) {
                try {
                    handleRequest(req);
                } catch(const Exceptions::EndSessionException&) {
                    keepRunning = false;
                }
            }
        }
    }
}

void Client::handleResponse(const std::string& response)
{
    std::cout << response << Utils::Logger::LF;
}

void Client::handleRequest(const std::string& request)
{
    *server_ << request << Utils::Logger::CRLF;

    if (request == "quit") {
        throw Exceptions::EndSessionException();
    }
}