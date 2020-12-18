#ifndef CPPLS2_CLIENT_DIRECTORYLISTINGCOMMAND_H
#define CPPLS2_CLIENT_DIRECTORYLISTINGCOMMAND_H

#include "Command.h"

namespace Commands {
    class DirectoryListingCommand : public Command
    {
    public:
        DirectoryListingCommand(asio::ip::tcp::iostream& server, const std::string& request, const std::vector<std::string>& args);
        bool Execute() override;
    };
}

#endif //CPPLS2_CLIENT_DIRECTORYLISTINGCOMMAND_H
