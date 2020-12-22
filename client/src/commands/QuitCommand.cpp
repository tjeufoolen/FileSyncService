#include "QuitCommand.h"

namespace Commands {
    QuitCommand::QuitCommand(asio::ip::tcp::iostream &server, const std::string &request,
                             const std::vector<std::string> &args, bool log)
         :  Command(server, request, args, log)
     {

     }

    bool QuitCommand::Execute()
    {
        server_ << request_ << Utils::Logger::CRLF;
        return false;
    }
}