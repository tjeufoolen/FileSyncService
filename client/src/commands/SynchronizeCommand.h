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
        static const int MODIFICATION_THRESHOLD_SECONDS { 5 };

        int changes_ { 0 };
    public:
        SynchronizeCommand(asio::ip::tcp::iostream& server, const std::string& request, const std::vector<std::string>& args);
        bool Execute() override;
    private:
        std::vector<DirectoryListingCommand::Item> GetDirectoryContents(const std::string& path);
        void CreateServerDirectory(const std::string& parent, const std::string& name);
        void CreateLocalDirectory(const std::string& path);
        void UploadFile(const std::string& localPath);
        void DownloadFile(const std::string& remotePath);
    };
}

#endif //CPPLS2_CLIENT_SYNCHRONIZECOMMAND_H
