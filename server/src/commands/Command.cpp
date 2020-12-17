#include "Command.h"

namespace Commands {
    Command::Command(asio::ip::tcp::iostream& client, const std::vector<std::string>& args)
            :   client_{client}
    {
        std::vector<std::string> commandArgs { args };
        commandArgs.erase(commandArgs.begin());
        args_ = commandArgs;
    }
}