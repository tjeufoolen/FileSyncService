#include "HelpCommand.h"

namespace Commands {
    HelpCommand::HelpCommand(asio::ip::tcp::iostream &server, const std::string &request,
                             const std::vector<std::string> &args, bool log)
         :  Command(server, request, args, log)
    {

    }

    bool HelpCommand::Execute()
    {
        if (doLogResponse_) {
            Utils::Logger::Inform(
                    "--------------------------------------------------------------------------------\n"
                    "COMMAND\t\t\t\t| DESCRIPTION\n"
                    "--------------------------------------------------------------------------------\n"
                    "help\t\t\t\t- shows this information\n"
                    "info\t\t\t\t- shows server information\n"
                    "dir <path>\t\t\t- shows the contents of specified directory\n"
                    "get <path>\t\t\t- downloads the specified file from the server\n"
                    "put <path>\t\t\t- uploads the local file to the server\n"
                    "ren <path> <new-name>\t\t- renames specified file\n"
                    "del <path>\t\t\t- deletes specified file\n"
                    "mkdir <parent-path> <name>\t- create a directory at the specified path\n"
                    "sync\t\t\t\t- synchronizes local and server directories\n"
                    "quit\t\t\t\t- closes the client\n"
            );
        }

        return true;
    }
}