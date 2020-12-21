#include "UploadFileCommand.h"

#include <filesystem>
#include <fstream>

#include "Client.h"

#define fs std::filesystem

namespace Commands {
    UploadFileCommand::UploadFileCommand(asio::ip::tcp::iostream &server, const std::string &request,
                                         const std::vector<std::string> &args, bool log)
         :  Command(server, request, args, log)
    {

    }

    bool UploadFileCommand::Execute()
    {
        if (commandArgs_.empty()) {
            if (doLogResponse_) Utils::Logger::error("Too less arguments specified.\nPlease specify the path to the local file.");
            return true;
        }
        else {
            auto path = std::string(Client::BASE_DIRECTORY).append(commandArgs_[0]);

            if (fs::exists(path) && !fs::is_directory(path)) {
                // 1. send name and file size to server
                auto bytes = fs::file_size(path);
                std::string request = std::string(request_).append(" ").append(std::to_string(bytes));
                server_ << request << Utils::Logger::CRLF;

                // 2. send actual file contents
                std::ifstream file{ path, std::ios::in | std::ios::binary };

                char* buffer = new char[bytes];
                file.read(buffer, bytes);

                server_.write(buffer, bytes);

                file.close();
                delete[] buffer;

                // 3. handle response
                Command::HandleResponse();
                return true;
            } else {
                if (doLogResponse_) Utils::Logger::error("Error: no such file");
                return true;
            }
        }
    }
}