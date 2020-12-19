#ifndef CPPLS2_SERVER_DOWNLOADFILECOMMAND_H
#define CPPLS2_SERVER_DOWNLOADFILECOMMAND_H

#include "Command.h"

namespace Commands {
    class DownloadFileCommand : public Command
    {
    public:
        DownloadFileCommand(asio::ip::tcp::iostream& client, const std::vector<std::string>& args);
        void Execute() override;
    };
}

#endif //CPPLS2_SERVER_DOWNLOADFILECOMMAND_H
