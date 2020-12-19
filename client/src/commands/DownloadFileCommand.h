#ifndef CPPLS2_CLIENT_DOWNLOADFILECOMMAND_H
#define CPPLS2_CLIENT_DOWNLOADFILECOMMAND_H

#include "Command.h"

namespace Commands {
    class DownloadFileCommand : public Command
    {
        std::string path_;
    public:
        DownloadFileCommand(asio::ip::tcp::iostream& server, const std::string& request, const std::vector<std::string>& args);

        bool Execute() override;
        void HandleResponse() override;
    };
}

#endif //CPPLS2_CLIENT_DOWNLOADFILECOMMAND_H
