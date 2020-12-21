#ifndef CPPLS2_CLIENT_DELETECOMMAND_H
#define CPPLS2_CLIENT_DELETECOMMAND_H

#include "Command.h"

namespace Commands {
    class DeleteCommand : public Command {
    public:
        DeleteCommand(asio::ip::tcp::iostream& server, const std::string& request, const std::vector<std::string>& args, bool log=true);

        bool Execute() override;
    };
}

#endif //CPPLS2_CLIENT_DELETECOMMAND_H
