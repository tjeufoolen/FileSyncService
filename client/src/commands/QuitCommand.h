#ifndef CPPLS2_CLIENT_QUITCOMMAND_H
#define CPPLS2_CLIENT_QUITCOMMAND_H

#include "Command.h"

namespace Commands {
    class QuitCommand : public Command
    {
    public:
        QuitCommand(asio::ip::tcp::iostream& server, const std::string& request, const std::vector<std::string>& args);

        bool Execute() override;
    };
}

#endif //CPPLS2_CLIENT_QUITCOMMAND_H
