#ifndef CPPLS2_SERVER_DIRECTORYLISTINGCOMMAND_H
#define CPPLS2_SERVER_DIRECTORYLISTINGCOMMAND_H

#include "Command.h"

namespace Commands {
    class DirectoryListingCommand : public Command
    {
    public:
        DirectoryListingCommand(asio::ip::tcp::iostream& client, const std::vector<std::string>& args);
        void Execute() override;
    };
}

#endif //CPPLS2_SERVER_DIRECTORYLISTINGCOMMAND_H
