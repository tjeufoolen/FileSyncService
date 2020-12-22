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
            if (doLogResponse_)
                Utils::Logger::Inform("Too less arguments specified.\nPlease specify the path to a directory.");
            return true;
        } else {
            path_ = commandArgs_[0];
            auto path { std::string(Client::BASE_DIRECTORY).append(path_) };

            if (fs::exists(path)) {
                server_ << request_ << Utils::Logger::CRLF;
                DirectoryListingCommand::HandleResponse();
                return true;
            } else {
                if (doLogResponse_) Utils::Logger::Error("Error: no such directory");
                return true;
            }
        }
    }

    void DirectoryListingCommand::HandleResponse()
    {
        if (!items_.empty()) items_.clear();

        std::string resp;

        try {
            // first get the amount of items that are getting returned
            getline(server_, resp);
            resp.erase(resp.end() - 1); // remove '\r'
            int totalItems { std::stoi(resp) };

            // get all items and print them
            while (totalItems > 0) {
                std::string item;
                getline(server_, item);
                item.erase(item.end() - 1); // remove '\r'

                if (doLogResponse_) Utils::Logger::Inform(item);
                SaveItemOutputHistory(item);

                totalItems--;
            }
        } catch(const std::invalid_argument&) {
            if (doLogResponse_) Utils::Logger::Error(resp);
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
        std::string& name { parts[1] };
        std::string& parentPath { path_ };
        std::string& modified_at { parts[2] };
        std::string& size { parts[3] };

        items_.emplace_back(type, name, parentPath, modified_at, size);
    }
}