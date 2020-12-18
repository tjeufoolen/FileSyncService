#include "InfoCommand.h"

namespace Commands {
    InfoCommand::InfoCommand(asio::ip::tcp::iostream &server, const std::string &request,
                             const std::vector<std::string> &args)
        :   Command(server, request, args)
    {

    }

    bool InfoCommand::Execute()
    {
        server_ << request_ << Utils::Logger::CRLF;
        return true;
    }
}