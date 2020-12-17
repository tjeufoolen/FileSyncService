#include "InfoCommand.h"
#include "Logger.h"

namespace Commands {
    InfoCommand::InfoCommand(asio::ip::tcp::iostream& client, const std::vector<std::string>& args)
            :   Command(client, args)
    {

    }

    void InfoCommand::Execute()
    {
        client_ << "AvanSync server 1.0, copyright (c) 2020 Bob Polis." << Utils::Logger::CRLF;
    }
}