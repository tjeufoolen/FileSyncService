#ifndef CPPLS2_CLIENT_HELPCOMMAND_H
#define CPPLS2_CLIENT_HELPCOMMAND_H

#include "Command.h"

namespace Commands {
    class HelpCommand : public Command
    {
    public:
        HelpCommand(asio::ip::tcp::iostream& server, const std::string& request, const std::vector<std::string>& args, bool log=true);

        bool Execute() override;
    };
}

#endif //CPPLS2_CLIENT_HELPCOMMAND_H
