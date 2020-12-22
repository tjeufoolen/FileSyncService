#ifndef CPPLS2_SERVER_UPLOADFILECOMMAND_H
#define CPPLS2_SERVER_UPLOADFILECOMMAND_H

#include "Command.h"

namespace Commands {
    class UploadFileCommand : public Command
    {
    public:
        UploadFileCommand(asio::ip::tcp::iostream& client, const std::vector<std::string>& args);
        void Execute() override;
    };
}

#endif //CPPLS2_SERVER_UPLOADFILECOMMAND_H
