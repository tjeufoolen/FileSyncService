#include "QuitCommand.h"

namespace Commands {
    QuitCommand::QuitCommand(asio::ip::tcp::iostream &server, const std::string &request,
                             const std::vector<std::string> &args)
         :  Command(server, request, args)
     {

     }

    bool QuitCommand::Execute()
    {
        server_ << request_ << Utils::Logger::CRLF;
        return false;
    }
}