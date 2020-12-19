#include "DirectoryListingCommand.h"

#include <filesystem>

#include "Client.h"

#define fs std::filesystem

namespace Commands {
    DirectoryListingCommand::DirectoryListingCommand(asio::ip::tcp::iostream &server, const std::string &request,
                                                     const std::vector<std::string> &args)
         :  Command(server, request, args)
    {

    }

    bool DirectoryListingCommand::Execute()
    {
        if (commandArgs_.empty()) {
            Utils::Logger::inform("Too less arguments specified.\nPlease specify the path to a directory.");
            return true;
        } else {
            auto path = std::string(Client::BASE_DIRECTORY).append(commandArgs_[0]);

            if (fs::exists(path)) {
                server_ << request_ << Utils::Logger::CRLF;
                DirectoryListingCommand::HandleResponse();
                return true;
            } else {
                Utils::Logger::error("Error: no such directory");
                return true;
            }
        }
    }

    void DirectoryListingCommand::HandleResponse()
    {
        int totalItems;

        // first get the amount of items that are getting returned
        std::string resp;
        getline(server_, resp);
        resp.erase(resp.end() - 1); // remove '\r'
        totalItems = std::stoi(resp);

        // get all items and print them
        while (totalItems > 0) {
            std::string item;
            getline(server_, item);
            item.erase(item.end() - 1); // remove '\r'

            Utils::Logger::inform(item);

            totalItems--;
        }
    }
}