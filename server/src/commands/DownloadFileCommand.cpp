#include "DownloadFileCommand.h"

#include <filesystem>
#include <fstream>

#include "Server.h"

#define fs std::filesystem

namespace Commands {
    DownloadFileCommand::DownloadFileCommand(asio::ip::tcp::iostream &client, const std::vector<std::string> &args)
        :   Command(client, args)
    {

    }

    void DownloadFileCommand::Execute()
    {
        if (!commandArgs_.empty())
        {
            std::string path = std::string(Server::BASE_DIRECTORY).append(commandArgs_[0]);

            if ((fs::status(path).permissions() & fs::perms::others_write) != fs::perms::none &&
                (fs::status(path).permissions() & fs::perms::others_exec)  != fs::perms::none)
            {
                if (!fs::is_directory(path) && fs::exists(path))
                {
                    // 1. Return the file size in bytes
                    auto bytes = fs::file_size(path);
                    client_ << bytes << Utils::Logger::CRLF;

                    // 2. Return the bytes
                    std::ifstream file{ path, std::ios::in | std::ios::binary };

                    char* buffer = new char[bytes];
                    file.read(buffer, bytes);

                    client_.write(buffer, bytes);

                    file.close();
                    delete[] buffer;
                }
                else {
                    client_ << "Error: no such file" << Utils::Logger::CRLF;
                }
            }
            else {
                client_ << "Error: no permission" << Utils::Logger::CRLF;
            }
        }
    }
}