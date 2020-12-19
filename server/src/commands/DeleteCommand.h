#ifndef CPPLS2_SERVER_DELETECOMMAND_H
#define CPPLS2_SERVER_DELETECOMMAND_H

#include "Command.h"

namespace Commands {
    class DeleteCommand : public Command
    {
    public:
        DeleteCommand(asio::ip::tcp::iostream& client, const std::vector<std::string>& args);
        void Execute() override;
    };
}

#endif //CPPLS2_SERVER_DELETECOMMAND_H
