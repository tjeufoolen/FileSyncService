#include "SynchronizeCommand.h"

#include <iostream>
#include <filesystem>

#include "Client.h"
#include "MakeDirectoryCommand.h"
#include "DownloadFileCommand.h"
#include "UploadFileCommand.h"
#include "TimestampConverter.h"

#define fs std::filesystem

namespace Commands {
    SynchronizeCommand::SynchronizeCommand(asio::ip::tcp::iostream &server, const std::string &request,
                                           const std::vector<std::string> &args)
            : Command(server, request, args) {

    }

    bool SynchronizeCommand::Execute()
    {
        // keep synchronizing until everything is up-to-date
        do {
            changes_ = 0;

            // List of all files and subdirectories on the server
            std::vector<DirectoryListingCommand::Item> serverItems{};

            // Helper lambdas
            auto getByName = [&](const std::string &name) -> auto {
                return std::find_if(begin(serverItems), end(serverItems),
                    [&](const DirectoryListingCommand::Item &item) {
                        return item.Name == name;
                });
            };

            // Get root directory contents and add to serverItems list
            auto rootItems{GetDirectoryContents("")};
            serverItems.insert(serverItems.begin(), rootItems.begin(), rootItems.end());

            // walk through all local files and subdirectories
            for (auto &local : fs::recursive_directory_iterator(Client::BASE_DIRECTORY)) {
                auto relativePath{fs::relative(local, Client::BASE_DIRECTORY).string()}; // private/example.txt
                std::string name{local.path().filename().string()}; // example.txt

                // check if item is directory
                if (fs::is_directory(local)) {
                    auto vec{GetDirectoryContents(relativePath)};
                    serverItems.insert(serverItems.begin(), vec.begin(), vec.end());

                    auto it{getByName(name)};

                    // when directory does not exist on server
                    if (it == serverItems.end()) {
                        CreateServerDirectory(fs::path(relativePath).remove_filename().string(), name);
                    }
                }

                    // check if item is file
                else if (fs::is_regular_file(local)) {
                    auto it{getByName(name)};

                    // check if file exists on server
                    if (it != serverItems.end()) {
                        auto &server{it};

                        auto l_modification_timestamp = Utils::TimestampConverter::ConvertStringToTimeT(
                                Utils::TimestampConverter::ConvertFileTimestamp(local.last_write_time()));
                        auto s_modification_timestamp = Utils::TimestampConverter::ConvertStringToTimeT(
                                server->ModifiedAt);

                        double differenceInSeconds = difftime(s_modification_timestamp, l_modification_timestamp);

                        // check if local item's modification date is newer then server
                        if (differenceInSeconds < MODIFICATION_THRESHOLD_SECONDS * -1) {
                            UploadFile(relativePath);   // overwrite server
                        }
                            // check if server's modification date is newer then local
                        else if (differenceInSeconds > MODIFICATION_THRESHOLD_SECONDS) {
                            DownloadFile(relativePath); // overwrite local
                        }
                    }

                        // upload file to server
                    else {
                        UploadFile(relativePath);
                    }
                }
            }

            // walk through all server files and subdirectories
            for (auto &server : serverItems) {
                std::string relativePath{std::string(server.Path).append("/").append(server.Name)};
                std::string localPath{std::string(Client::BASE_DIRECTORY).append("/").append(relativePath)};

                // when item is a directory
                if (server.Type == DirectoryListingCommand::ItemType::DIRECTORY) {
                    // check if directory exists local
                    if (!fs::exists(localPath)) {
                        // if it doesn't exist create it
                        CreateLocalDirectory(localPath);
                    }
                }

                    // when item is a file
                else if (server.Type == DirectoryListingCommand::ItemType::FILE) {
                    // check if file exists local
                    if (!fs::exists(localPath)) {
                        // if it doesn't exist download it
                        DownloadFile(relativePath);
                    }
                }
            }
        } while(changes_ != 0);

        return true;
    }

    std::vector<DirectoryListingCommand::Item> SynchronizeCommand::GetDirectoryContents(const std::string &path)
    {
        std::string path_{path};
        if (path_.empty()) path_ = ".";

        std::string prefix{"DIR"};
        std::string request{std::string(prefix).append(" ").append(path_)};
        std::vector<std::string> args{prefix, path_};

        auto command{DirectoryListingCommand{server_, request, args, false}};
        command.Execute();

        return command.GetItems();
    }

    void SynchronizeCommand::CreateServerDirectory(const std::string &parent, const std::string &name)
    {
        std::string parentDir{parent};
        if (parentDir.empty()) parentDir = ".";

        std::string prefix{"MKDIR"};
        std::string request{std::string(prefix).append(" ").append(parentDir).append(" ").append(name)};
        std::vector<std::string> args{prefix, parentDir, name};

        Utils::Logger::Inform(std::string("Creating directory '").append(name).append("' on server..."));
        changes_++;

        auto command{MakeDirectoryCommand{server_, request, args, false}};
        command.Execute();
    }

    void SynchronizeCommand::CreateLocalDirectory(const std::string &path)
    {
        Utils::Logger::Inform(std::string("Creating directory '").append(path).append("' local..."));
        changes_++;

        fs::create_directory(path);
    }

    void SynchronizeCommand::DownloadFile(const std::string &remotePath)
    {
        std::string prefix{"GET"};
        std::string request{std::string(prefix).append(" ").append(remotePath)};
        std::vector<std::string> args{prefix, remotePath};

        Utils::Logger::Inform(std::string("Downloading ").append(remotePath).append(" from server..."));
        changes_++;

        auto command{DownloadFileCommand{server_, request, args, false}};
        command.Execute();
    }

    void SynchronizeCommand::UploadFile(const std::string &localPath)
    {
        std::string prefix{"PUT"};
        std::string request{std::string(prefix).append(" ").append(localPath)};
        std::vector<std::string> args{prefix, localPath};

        Utils::Logger::Inform(std::string("Uploading ").append(localPath).append(" to server..."));
        changes_++;

        auto command{UploadFileCommand{server_, request, args, false}};
        command.Execute();
    }
}