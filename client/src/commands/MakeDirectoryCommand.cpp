#include "MakeDirectoryCommand.h"

#include <filesystem>

#include "Client.h"

#define fs std::filesystem

namespace Commands {
    MakeDirectoryCommand::MakeDirectoryCommand(asio::ip::tcp::iostream &server, const std::string& request, const std::vector<std::string> &args)
        :   Command(server, request, args)
    {

    }

    void MakeDirectoryCommand::Execute()
    {
        if (commandArgs_.size() >= 2) {
            auto parentDir = std::string(Client::BASE_DIRECTORY).append(commandArgs_[0]);
            auto& name = commandArgs_[1];

            if (fs::exists(parentDir)) {
                fs::create_directory(std::string(parentDir).append("/").append(name));
            }
        }

        server_ << request_ << Utils::Logger::CRLF;
    }
}