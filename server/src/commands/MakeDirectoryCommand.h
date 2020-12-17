#ifndef CPPLS2_SERVER_MAKEDIRECTORYCOMMAND_H
#define CPPLS2_SERVER_MAKEDIRECTORYCOMMAND_H

#include "Command.h"

namespace Commands {
    class MakeDirectoryCommand : public Command
    {
    public:
        MakeDirectoryCommand(asio::ip::tcp::iostream& client, const std::vector<std::string>& args);
        void Execute() override;
    };
}

#endif //CPPLS2_SERVER_MAKEDIRECTORYCOMMAND_H
