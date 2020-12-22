#ifndef CPPLS2_CLIENT_UPLOADFILECOMMAND_H
#define CPPLS2_CLIENT_UPLOADFILECOMMAND_H

#include "Command.h"

namespace Commands {
    class UploadFileCommand : public Command
    {
    public:
        UploadFileCommand(asio::ip::tcp::iostream& server, const std::string& request, const std::vector<std::string>& args, bool log=true);

        bool Execute() override;
    };
}

#endif //CPPLS2_CLIENT_UPLOADFILECOMMAND_H
