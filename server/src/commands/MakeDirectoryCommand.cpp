#include "MakeDirectoryCommand.h"

#include <filesystem>
#include <iostream>

#include "Server.h"

#define fs std::filesystem

namespace Commands {
    MakeDirectoryCommand::MakeDirectoryCommand(asio::ip::tcp::iostream& client, const std::vector<std::string>& args)
            :   Command(client, args)
    {

    }

    void MakeDirectoryCommand::Execute()
    {
        if (commandArgs_.size() >= 2)
        {
            std::string parentDir = std::string(Server::BASE_DIRECTORY).append(commandArgs_[0]);
            std::string& name = commandArgs_[1];

            if ((fs::status(parentDir).permissions() & fs::perms::others_write) != fs::perms::none &&
                (fs::status(parentDir).permissions() & fs::perms::others_exec)  != fs::perms::none)
            {
                if (fs::exists(parentDir))
                {
                    fs::create_directory(std::string(parentDir).append("/").append(name));
                    client_ << "OK" << Utils::Logger::CRLF;
                }
                else {
                    client_ << "Error: no such directory" << Utils::Logger::CRLF;
                }
            }
            else {
                client_ << "Error: no permission" << Utils::Logger::CRLF;
            }
        }
    }
}