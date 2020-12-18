#ifndef CPPLS2_CLIENT_RENAMECOMMAND_H
#define CPPLS2_CLIENT_RENAMECOMMAND_H

#include "Command.h"

namespace Commands {
    class RenameCommand : public Command
    {
    public:
        RenameCommand(asio::ip::tcp::iostream& server, const std::string& request, const std::vector<std::string>& args);
        bool Execute() override;
    };
}

#endif //CPPLS2_CLIENT_RENAMECOMMAND_H
