#include "SynchronizeCommand.h"

#include <iostream>
#include <filesystem>

#include "Client.h"
#include "MakeDirectoryCommand.h"
#include "DownloadFileCommand.h"
#include "UploadFileCommand.h"

#define fs std::filesystem

namespace Commands {
    SynchronizeCommand::SynchronizeCommand(asio::ip::tcp::iostream &server, const std::string &request,
                                           const std::vector<std::string> &args)
       :    Command(server, request, args)
   {

   }

   bool SynchronizeCommand::Execute()
   {
        // To synchronize both client and server directories, we need to loop through all local and server
        // subdirectories recursively and check which subdirectories and files do not exist on either end.
        // We also need to check if both timestamps are equal. If not, we should overwrite the file contents with the
        // oldest modification date with the contents of the file with the newer modification date.
        //
        // If this is done correctly, both directories should have the same files and subdirectories.

       for(auto& localItem : fs::recursive_directory_iterator(Client::BASE_DIRECTORY))
       {
            std::string relativePath { fs::relative(localItem, Client::BASE_DIRECTORY).generic_string() };

            
       }

       return true;
   }

    std::vector<DirectoryListingCommand::Item> SynchronizeCommand::GetDirectoryContents(const std::string &path)
   {
        std::string prefix { "DIR" };
        std::string request { std::string(prefix).append(" ").append(path) };
        std::vector<std::string> args {prefix, path};

        auto command = DirectoryListingCommand{server_, request, args, false};
        command.Execute();

        return command.GetItems();
   }

   void SynchronizeCommand::MakeDirectory(const std::string &parent, const std::string &name)
   {
       std::string prefix { "MKDIR" };
       std::string request { std::string(prefix).append(" ").append(parent).append(" ").append(name) };
       std::vector<std::string> args {prefix, parent, name};

       auto command = MakeDirectoryCommand{server_, request, args};
       command.Execute();
   }

   void SynchronizeCommand::DownloadFile(const std::string &remotePath)
   {
       std::string prefix { "GET" };
       std::string request { std::string(prefix).append(" ").append(remotePath) };
       std::vector<std::string> args {prefix, remotePath};

       auto command = DownloadFileCommand{server_, request, args};
       command.Execute();
   }

   void SynchronizeCommand::UploadFile(const std::string &localPath)
   {
       std::string prefix { "PUT" };
       std::string request { std::string(prefix).append(" ").append(localPath) };
       std::vector<std::string> args {prefix, localPath};

       auto command = UploadFileCommand{server_, request, args};
       command.Execute();
   }
}