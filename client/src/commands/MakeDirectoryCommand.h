#ifndef CPPLS2_CLIENT_MAKEDIRECTORYCOMMAND_H
#define CPPLS2_CLIENT_MAKEDIRECTORYCOMMAND_H

#include "Command.h"

namespace Commands {
    class MakeDirectoryCommand : public Command
    {
    public:
        MakeDirectoryCommand(asio::ip::tcp::iostream& server, const std::string& request, const std::vector<std::string>& args);

        bool Execute() override;
    };
}

#endif //CPPLS2_CLIENT_MAKEDIRECTORYCOMMAND_H
