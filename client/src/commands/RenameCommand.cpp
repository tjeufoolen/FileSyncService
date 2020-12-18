#include "RenameCommand.h"

#include <filesystem>

#include "Client.h"

#define fs std::filesystem

namespace Commands {
    RenameCommand::RenameCommand(asio::ip::tcp::iostream &server, const std::string &request,
                                 const std::vector<std::string> &args)
        :   Command(server, request, args)
    {

    }

    bool RenameCommand::Execute()
    {
        if (commandArgs_.size() < 2) {
            Utils::Logger::error("Too less arguments specified.\nPlease specify the path to a file or directory and the new name.");
            return false;
        }
        else {
            auto path = std::string(Client::BASE_DIRECTORY).append(commandArgs_[0]);
            auto newName = commandArgs_[1];
            auto newPath = fs::path(std::string(path)).parent_path().generic_string().append("/").append(commandArgs_[1]);

            if (fs::exists(path)) {
                fs::rename(path, newPath);

                server_ << request_ << Utils::Logger::CRLF;
                return true;
            } else {
                Utils::Logger::error("Error: no such file or directory");
                return false;
            }
        }
    }
}