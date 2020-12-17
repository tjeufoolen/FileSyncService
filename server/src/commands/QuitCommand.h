#ifndef CPPLS2_SERVER_QUITCOMMAND_H
#define CPPLS2_SERVER_QUITCOMMAND_H

#include "Command.h"

namespace Commands {
    class QuitCommand : public Command
    {
    public:
        QuitCommand(asio::ip::tcp::iostream& client, const std::vector<std::string>& args);
        void Execute() override;
    };
}

#endif //CPPLS2_SERVER_QUITCOMMAND_H
