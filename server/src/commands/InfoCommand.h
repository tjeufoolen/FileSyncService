#ifndef CPPLS2_SERVER_INFOCOMMAND_H
#define CPPLS2_SERVER_INFOCOMMAND_H

#include "Command.h"

namespace Commands {
    class InfoCommand : public Command
    {
    public:
        InfoCommand(asio::ip::tcp::iostream& client, const std::vector<std::string>& args);
        void Execute() override;
    };
}

#endif //CPPLS2_SERVER_INFOCOMMAND_H
