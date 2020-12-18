#include "DirectoryListingCommand.h"

#include <filesystem>

#include "Server.h"
#include "TimestampConverter.h"

#define fs std::filesystem

namespace Commands {
    DirectoryListingCommand::DirectoryListingCommand(asio::ip::tcp::iostream &client,
                                                     const std::vector<std::string> &args)
         :  Command(client, args)
    {

    }

    void DirectoryListingCommand::Execute()
    {
        if (!commandArgs_.empty())
        {
            auto path = std::string(Server::BASE_DIRECTORY).append(commandArgs_[0]);

            if ((fs::status(path).permissions() & fs::perms::others_read) != fs::perms::none &&
                (fs::status(path).permissions() & fs::perms::others_exec)  != fs::perms::none)
            {
                if (fs::exists(path) && fs::is_directory(path))
                {
                    // Send the amount of items the directory contains
                    unsigned int count = std::distance(fs::directory_iterator(path), fs::directory_iterator{});
                    client_ << count << Utils::Logger::CRLF;

                    // Send the items (one at a time)
                    for (const auto& entry : fs::directory_iterator(path))
                    {
                        const char type = entry.is_symlink() ? '*' : entry.is_directory() ? 'D' : entry.is_regular_file() ? 'F' : '*';
                        const std::string name = entry.path().filename().string();
                        const std::string modified_at = Utils::TimestampConverter::convertFileTimestamp(entry.last_write_time());
                        const std::string size = entry.is_regular_file() ? std::to_string(entry.file_size()) : "0";

                        client_ << type << "|" << name << "|" << modified_at << "|" << size << Utils::Logger::CRLF;
                    }
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