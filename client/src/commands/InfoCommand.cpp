#include "InfoCommand.h"

namespace Commands {
    InfoCommand::InfoCommand(asio::ip::tcp::iostream &server, const std::string &request,
                             const std::vector<std::string> &args, bool log)
        :   Command(server, request, args, log)
    {

    }

    bool InfoCommand::Execute()
    {
        server_ << request_ << Utils::Logger::CRLF;
        Command::HandleResponse();
        return true;
    }
}