#include "DownloadFileCommand.h"

#include <filesystem>
#include <fstream>

#include "Client.h"

#define fs std::filesystem

namespace Commands {
    DownloadFileCommand::DownloadFileCommand(asio::ip::tcp::iostream &server, const std::string &request,
                                             const std::vector<std::string> &args)
         :  Command(server, request, args)
    {

    }

    bool DownloadFileCommand::Execute()
    {
        if (commandArgs_.empty()) {
            Utils::Logger::inform("Too less arguments specified.\nPlease specify the path to a file.");
            return true;
        } else {
            if (!path_.empty()) path_.clear();
            path_ = std::string(Client::BASE_DIRECTORY).append(commandArgs_[0]);

            server_ << request_ << Utils::Logger::CRLF;
            DownloadFileCommand::HandleResponse();
            return true;
        }
    }

    void DownloadFileCommand::HandleResponse()
    {
        // Retrieve the first response
        std::string resp;
        getline(server_, resp);
        resp.erase(resp.end() - 1); // remove '\r'

        // If the response is an error, print it
        if (resp.rfind("Error: ", 0) == 0) {
            Utils::Logger::inform(resp);
        }

        // Otherwise the response is the amount of bytes the file is long
        // so we know how much we need to read
        else {
            auto bytes = stoi(resp);

            // read from server
            char* buffer = new char[bytes];
            server_.read(buffer, bytes);

            // create file
            std::ofstream file{ path_, std::ios::out | std::ios::binary };

            // write to file
            file.write(buffer, bytes);

            // cleanup
            file.close();
            delete[] buffer;
        }
    }
}