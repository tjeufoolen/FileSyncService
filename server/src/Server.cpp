#include "Server.h"

#include <filesystem>
#include <iostream>

#include "StringSplitter.h"
#include "Logger.h"
#include "ClientDisconnectException.h"
#include "InfoCommand.h"
#include "QuitCommand.h"

Server::Server(int port, const std::string &baseDirectory)
    :   PORT{port},
        BASE_DIRECTORY{std::filesystem::current_path().generic_string().append("/dropbox/")}
{
    start();
}

void Server::start()
{
    server_ = std::make_unique<asio::ip::tcp::acceptor>(io_context_, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), PORT));

    if (server_) {
        run();
    }
}

void Server::run()
{
    for (;;)
    {
        std::cerr << "waiting for client to connect\n";

        asio::ip::tcp::iostream client;
        server_->accept(client.socket());
        std::cerr << "client connected from " << client.socket().local_endpoint() << Utils::Logger::LF;

        client << "Welcome to AvanSync server 1.0" << Utils::Logger::CRLF;

        bool keepListening{true};
        while (keepListening)
        {
            std::string request;
            getline(client, request);
            request.erase(request.end() - 1); // remove '\r'
            std::cerr << "client says: " << request << Utils::Logger::LF;

            try {
                std::unique_ptr<std::vector<std::string>> args = std::move(Utils::StringSplitter::Split(request, ' '));
                handleRequest(client, *args);
            } catch(const Exceptions::ClientDisconnectException&) {
                keepListening = false;
            }
        }
    }
}

void Server::handleRequest(asio::ip::tcp::iostream& client, const std::vector<std::string>& args)
{
    if (args.empty()) return; // todo: handle empty request

    if (args[0] == "info") {
        Commands::InfoCommand{client, args}.Execute();
    }

    else if (args[0] == "quit") {
        Commands::QuitCommand{client, args}.Execute();
    }

    // todo: handle invalid request
}