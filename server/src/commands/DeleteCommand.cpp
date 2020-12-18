#include "DeleteCommand.h"

#include <filesystem>

#include "Server.h"

#define fs std::filesystem

namespace Commands {
    DeleteCommand::DeleteCommand(asio::ip::tcp::iostream &client, const std::vector<std::string> &args)
        :   Command(client, args)
    {

    }

    void DeleteCommand::Execute()
    {
        if (!commandArgs_.empty())
        {
            auto path = std::string(Server::BASE_DIRECTORY).append(commandArgs_[0]);

            if ((fs::status(path).permissions() & fs::perms::others_write) != fs::perms::none &&
                (fs::status(path).permissions() & fs::perms::others_exec)  != fs::perms::none)
            {
                if (fs::exists(path))
                {
                    fs::remove_all(path);
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