#include "Client.h"

#include <filesystem>
#include <iostream>

#include "Logger.h"
#include "StringSplitter.h"
#include "MakeDirectoryCommand.h"

const std::string Client::BASE_DIRECTORY = {std::filesystem::current_path().generic_string().append("/dropbox/")};

Client::Client(const std::string& hostname, const std::string& port)
    : HOSTNAME{hostname},
      PORT{port}
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
                if (req != "quit") {
                    std::unique_ptr<std::vector<std::string>> args = std::move(Utils::StringSplitter::Split(req, ' '));
                    handleRequest(req, *args);
                } else {
                    *server_ << req << Utils::Logger::CRLF;
                    keepRunning = false;
                    break;
                }
            }
        }
    }
}

void Client::handleResponse(const std::string& response)
{
    std::cout << response << Utils::Logger::LF;
}

void Client::handleRequest(const std::string& request, const std::vector<std::string>& args)
{
    if (args.empty()) return; // todo: handle no arguments provided

    // complex commands
    if (args[0] == "mkdir") {
        Commands::MakeDirectoryCommand{*server_, request, args}.Execute();
    }

    // simple commands
    else {
        *server_ << request << Utils::Logger::CRLF;
    }

    // todo: handle invalid action?
}