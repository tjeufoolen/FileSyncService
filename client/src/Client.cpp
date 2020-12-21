#include "Client.h"

#include <filesystem>
#include <iostream>

#include "Logger.h"
#include "StringSplitter.h"
#include "MakeDirectoryCommand.h"
#include "InfoCommand.h"
#include "DeleteCommand.h"
#include "RenameCommand.h"
#include "DirectoryListingCommand.h"
#include "QuitCommand.h"
#include "DownloadFileCommand.h"
#include "UploadFileCommand.h"
#include "SynchronizeCommand.h"

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
    if (*server_) {
        // Retrieve welcome message
        std::string message;
        getline(*server_, message);
        message.erase(message.end() - 1); // remove '\r'
        Utils::Logger::inform(message);

        // Keep handling requests until specified not to
        bool keepRunning{true};
        while (keepRunning && *server_)
        {
            std::cout << Utils::Logger::PREFIX << std::flush;
            std::string req;

            // get user input
            getline(std::cin, req);

            // handle request
            std::unique_ptr<std::vector<std::string>> args = std::move(Utils::StringSplitter::Split(req, ' '));
            keepRunning = handleCommand(req, *args);
        }
    }
}

bool Client::handleCommand(const std::string &request, const std::vector<std::string> &args)
{
    // handle no arguments provided
    if (args.empty()) {
        Utils::Logger::inform("Please specify a valid command.");
        return true;
    }

    // execute specified command
    std::string cmd = args[0];
    std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::tolower);

    if (cmd == "quit") {
        return Commands::QuitCommand{*server_, request, args}.Execute();
    }
    else if (cmd == "mkdir") {
        return Commands::MakeDirectoryCommand{*server_, request, args}.Execute();
    }
    else if (cmd == "info") {
        return Commands::InfoCommand{*server_, request, args}.Execute();
    }
    else if (cmd == "del") {
        return Commands::DeleteCommand{*server_, request, args}.Execute();
    }
    else if (cmd == "ren") {
        return Commands::RenameCommand{*server_, request, args}.Execute();
    }
    else if (cmd == "dir") {
        return Commands::DirectoryListingCommand{*server_, request, args}.Execute();
    }
    else if (cmd == "get") {
        return Commands::DownloadFileCommand{*server_, request, args}.Execute();
    }
    else if (cmd == "put") {
        return Commands::UploadFileCommand{*server_, request, args}.Execute();
    }
    else if (cmd == "sync") {
        return Commands::SynchronizeCommand{*server_, request, args}.Execute();
    }

    // If we got here, it means that the command entered is not defined.
    Utils::Logger::inform("The command you entered does not exist.");
    return true;
}