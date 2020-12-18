#ifndef CPPLS2_CLIENT_COMMAND_H
#define CPPLS2_CLIENT_COMMAND_H

#include "ICommand.h"
#include "asio.hpp"
#include "Logger.h"

namespace Commands {
    class Command : public ICommand
    {
    public:
        Command(asio::ip::tcp::iostream& server, const std::string& request, const std::vector<std::string>& args);

        virtual bool Execute() = 0;
    protected:
        asio::ip::tcp::iostream& server_;
        std::string request_;
        std::vector<std::string> args_;
        std::vector<std::string> commandArgs_;
    };
}

#endif //CPPLS2_CLIENT_COMMAND_H
