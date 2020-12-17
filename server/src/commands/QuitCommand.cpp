#include "QuitCommand.h"

#include <numeric>

#include "Logger.h"
#include "ClientDisconnectException.h"

namespace Commands {
    QuitCommand::QuitCommand(asio::ip::tcp::iostream& client, const std::vector<std::string>& args)
            :   Command(client, args)
    {

    }

    void QuitCommand::Execute()
    {
        std::string request = std::accumulate(args_.begin(), args_.end(), std::string(" "));
        client_ << request << Utils::Logger::CRLF;
        throw Exceptions::ClientDisconnectException();
    }
}