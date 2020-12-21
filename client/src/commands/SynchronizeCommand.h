#ifndef CPPLS2_CLIENT_SYNCHRONIZECOMMAND_H
#define CPPLS2_CLIENT_SYNCHRONIZECOMMAND_H

#include "Command.h"

#include <map>
#include <vector>
#include <string>

#include "DirectoryListingCommand.h"

namespace Commands {
    class SynchronizeCommand : public Command
    {
    public:
        SynchronizeCommand(asio::ip::tcp::iostream& server, const std::string& request, const std::vector<std::string>& args);
        bool Execute() override;
    private:
        std::vector<DirectoryListingCommand::Item> GetDirectoryContents(const std::string& path);
        void MakeDirectory(const std::string& parent, const std::string& name);
        void UploadFile(const std::string& localPath);
        void DownloadFile(const std::string& remotePath);
    };
}

#endif //CPPLS2_CLIENT_SYNCHRONIZECOMMAND_H
