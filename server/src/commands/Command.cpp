#include "Command.h"

namespace Commands {
    Command::Command(asio::ip::tcp::iostream& client, const std::vector<std::string>& args)
            :   client_{client},
                args_{args},
                commandArgs_{args}
    {
        commandArgs_.erase(commandArgs_.begin()); // remove actual command from args
    }
}