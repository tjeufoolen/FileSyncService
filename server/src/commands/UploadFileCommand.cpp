#include "UploadFileCommand.h"

#include <filesystem>
#include <fstream>

#include "Server.h"

#define fs std::filesystem

namespace Commands {
    UploadFileCommand::UploadFileCommand(asio::ip::tcp::iostream &client, const std::vector<std::string> &args)
        :   Command(client, args)
    {

    }

    void UploadFileCommand::Execute()
    {
        if (commandArgs_.size() >= 2)
        {
            std::string path = std::string(Server::BASE_DIRECTORY).append(commandArgs_[0]);
            auto bytes = stoi(commandArgs_[1]);

            if ((fs::status(path).permissions() & fs::perms::others_read) != fs::perms::none &&
                (fs::status(path).permissions() & fs::perms::others_exec)  != fs::perms::none)
            {
                if (fs::space(fs::path(path).remove_filename().generic_string()).available >= bytes)
                {
                    // read from server
                    std::unique_ptr<char> buffer { std::make_unique<char>(bytes) };
                    client_.read(buffer.get(), bytes);

                    // create file
                    std::ofstream file{ path, std::ios::out | std::ios::binary };

                    // write to file
                    file.write(buffer.get(), bytes);

                    // cleanup
                    file.close();

                    client_ << "OK" << Utils::Logger::CRLF;
                }
                else {
                    client_ << "Error: not enough disk space" << Utils::Logger::CRLF;
                }
            }
            else {
                client_ << "Error: no permission" << Utils::Logger::CRLF;
            }
        }
    }
}