#ifndef CPPLS2_SERVER_RENAMECOMMAND_H
#define CPPLS2_SERVER_RENAMECOMMAND_H

#include "Command.h"

namespace Commands {
    class RenameCommand : public Command
    {
    public:
        RenameCommand(asio::ip::tcp::iostream& client, const std::vector<std::string>& args);
        void Execute() override;
    };
}

#endif //CPPLS2_SERVER_RENAMECOMMAND_H
