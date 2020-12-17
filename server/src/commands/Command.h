#ifndef CPPLS2_SERVER_COMMAND_H
#define CPPLS2_SERVER_COMMAND_H

#include "ICommand.h"
#include <asio.hpp>

namespace Commands {
    class Command : public ICommand
    {
    public:
        Command(asio::ip::tcp::iostream& client, const std::vector<std::string>& args);

        virtual void Execute() = 0;
    protected:
        asio::ip::tcp::iostream& client_;
        std::vector<std::string> args_;
    };
}

#endif //CPPLS2_SERVER_COMMAND_H
