#include "DeleteCommand.h"

#include <filesystem>

#include "Client.h"

#define fs std::filesystem

namespace Commands {
    DeleteCommand::DeleteCommand(asio::ip::tcp::iostream &server, const std::string &request,
                                 const std::vector<std::string> &args)
         :  Command(server, request, args)
    {

    }

    bool DeleteCommand::Execute()
    {
        if (commandArgs_.empty()) {
            Utils::Logger::inform("Too less arguments specified.\nPlease specify the path to a file or directory.");
            return false;
        } else {
            auto path = std::string(Client::BASE_DIRECTORY).append(commandArgs_[0]);

            if (fs::exists(path)) {
                fs::remove_all(path);

                server_ << request_ << Utils::Logger::CRLF;
                return true;
            } else {
                Utils::Logger::error("Error: Specified file or directory does not exist.");
                return false;
            }
        }
    }
}