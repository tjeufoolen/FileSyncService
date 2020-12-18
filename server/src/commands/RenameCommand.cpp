#include "RenameCommand.h"

#include <filesystem>

#include "Server.h"

#define fs std::filesystem

namespace Commands {
    RenameCommand::RenameCommand(asio::ip::tcp::iostream &client, const std::vector<std::string> &args)
        :   Command(client, args)
    {

    }

    void RenameCommand::Execute()
    {
        if (commandArgs_.size() >= 2)
        {
            auto path = std::string(Server::BASE_DIRECTORY).append(commandArgs_[0]);
            auto newName = commandArgs_[1];
            auto newPath = fs::path(std::string(path)).parent_path().generic_string().append("/").append(commandArgs_[1]);

            if ((fs::status(path).permissions() & fs::perms::others_write) != fs::perms::none &&
                (fs::status(path).permissions() & fs::perms::others_exec)  != fs::perms::none)
            {
                if (fs::exists(path))
                {
                    fs::rename(path, newPath);

                    client_ << "OK" << Utils::Logger::CRLF;
                }
                else {
                    client_ << "Error: no such file or directory" << Utils::Logger::CRLF;
                }
            }
            else {
                client_ << "Error: no permission" << Utils::Logger::CRLF;
            }
        }
    }
}