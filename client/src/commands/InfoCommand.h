#ifndef CPPLS2_CLIENT_INFOCOMMAND_H
#define CPPLS2_CLIENT_INFOCOMMAND_H

#include "Command.h"

namespace Commands {
    class InfoCommand : public Command
    {
    public:
        InfoCommand(asio::ip::tcp::iostream& server, const std::string& request, const std::vector<std::string>& args);

        bool Execute() override;
    };
}

#endif //CPPLS2_CLIENT_INFOCOMMAND_H
