#include "Command.h"

#include "Logger.h"

namespace Commands {
    Command::Command(asio::ip::tcp::iostream &server, const std::string& request, const std::vector<std::string> &args, bool log)
        :   server_{server},
            request_{request},
            response_{""},
            args_{args},
            commandArgs_{args},
            doLogResponse_{log}
    {
        if (!commandArgs_.empty()) commandArgs_.erase(commandArgs_.begin()); // remove actual command from args
    }

    void Command::HandleResponse()
    {
        if (!response_.empty()) response_.clear();

        getline(server_, response_);
        response_.erase(response_.end() - 1); // remove '\r'

        if (doLogResponse_) Utils::Logger::Inform(response_);
    }
}