#include "InfoCommand.h"
#include "Logger.h"

namespace Commands {
    InfoCommand::InfoCommand(asio::ip::tcp::iostream& client, const std::vector<std::string>& args)
            :   Command(client, args)
    {

    }

    void InfoCommand::Execute()
    {
        client_ << "Dropbox server 1.0, copyright (c) 2021 Tjeu Foolen." << Utils::Logger::CRLF;
    }
}