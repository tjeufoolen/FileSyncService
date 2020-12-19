#include "Server.h"

#include <filesystem>
#include <iostream>

#include "StringSplitter.h"
#include "Logger.h"
#include "InfoCommand.h"
#include "MakeDirectoryCommand.h"
#include "DeleteCommand.h"
#include "RenameCommand.h"
#include "DirectoryListingCommand.h"

const std::string Server::BASE_DIRECTORY = {std::filesystem::current_path().generic_string().append("/dropbox/")};

Server::Server(int port)
    :   PORT{port}
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

[[noreturn]] void Server::run()
{
    for (;;)
    {
        std::cerr << "waiting for client to connect\n";

        asio::ip::tcp::iostream client;
        server_->accept(client.socket());
        std::cerr << "client connected from " << client.socket().local_endpoint() << Utils::Logger::LF;

        client << "Welcome to Dropbox server 1.0" << Utils::Logger::CRLF;

        bool keepListening{true};
        while (keepListening)
        {
            std::string request;
            getline(client, request);
            request.erase(request.end() - 1); // remove '\r'
            std::cerr << "client says: " << request << Utils::Logger::LF;

            if (request != "quit") {
                std::unique_ptr<std::vector<std::string>> args = std::move(Utils::StringSplitter::Split(request, ' '));
                handleRequest(client, *args);
            } else {
                keepListening = false;
            }
        }
    }
}

void Server::handleRequest(asio::ip::tcp::iostream& client, const std::vector<std::string>& args)
{
    if (args.empty()) return;

    // execute specified command
    std::string cmd = args[0];
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

    if (cmd == "info") {
        Commands::InfoCommand{client, args}.Execute();
    }
    else if (cmd == "mkdir") {
        Commands::MakeDirectoryCommand{client, args}.Execute();
    }
    else if (cmd == "del") {
        Commands::DeleteCommand{client, args}.Execute();
    }
    else if (cmd == "ren") {
        Commands::RenameCommand{client, args}.Execute();
    }
    else if (cmd == "dir") {
        Commands::DirectoryListingCommand{client, args}.Execute();
    }
}