#include "Command.h"

namespace Commands {
    Command::Command(asio::ip::tcp::iostream &server, const std::string& request, const std::vector<std::string> &args)
        :   server_{server},
            request_{request},
            args_{args},
            commandArgs_{args}
    {
        commandArgs_.erase(commandArgs_.begin()); // remove actual command from args
    }
}