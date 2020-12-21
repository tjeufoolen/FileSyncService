#include "DirectoryListingCommand.h"

#include <filesystem>

#include "Client.h"
#include "StringSplitter.h"

#define fs std::filesystem

namespace Commands {
    DirectoryListingCommand::DirectoryListingCommand(asio::ip::tcp::iostream &server, const std::string &request,
                                                     const std::vector<std::string> &args, bool log)
         :  Command(server, request, args, log),
            items_{}
    {

    }

    bool DirectoryListingCommand::Execute()
    {
        if (commandArgs_.empty()) {
            if (doLogResponse_) Utils::Logger::inform("Too less arguments specified.\nPlease specify the path to a directory.");
            return true;
        } else {
            auto path = std::string(Client::BASE_DIRECTORY).append(commandArgs_[0]);

            if (fs::exists(path)) {
                server_ << request_ << Utils::Logger::CRLF;
                DirectoryListingCommand::HandleResponse();
                return true;
            } else {
                if (doLogResponse_) Utils::Logger::error("Error: no such directory");
                return true;
            }
        }
    }

    void DirectoryListingCommand::HandleResponse()
    {
        if (!items_.empty()) items_.clear();

        // first get the amount of items that are getting returned
        std::string resp;
        getline(server_, resp);
        resp.erase(resp.end() - 1); // remove '\r'
        int totalItems = std::stoi(resp);

        // get all items and print them
        while (totalItems > 0) {
            std::string item;
            getline(server_, item);
            item.erase(item.end() - 1); // remove '\r'

            if (doLogResponse_) Utils::Logger::inform(item);
            SaveItemOutputHistory(item);

            totalItems--;
        }
    }

    std::vector<DirectoryListingCommand::Item> DirectoryListingCommand::GetItems() const
    {
        return items_;
    }

    void DirectoryListingCommand::SaveItemOutputHistory(const std::string &output)
    {
        std::vector<std::string> parts { *std::move(Utils::StringSplitter::Split(output, '|')) };

        ItemType type { parts[0] == "F" ? ItemType::FILE : parts[0] == "D" ? ItemType::DIRECTORY : ItemType::OTHER };
        std::string& name = parts[1];
        long long modified_at = stol(parts[2]);
        long long size = stol(parts[3]);

        items_.emplace_back(type, name, modified_at, size);
    }
}