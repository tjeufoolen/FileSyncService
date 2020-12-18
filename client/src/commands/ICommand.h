#ifndef CPPLS2_CLIENT_ICOMMAND_H
#define CPPLS2_CLIENT_ICOMMAND_H

namespace Commands {
    struct ICommand
    {
        // The boolean return types specifies if the command should expect a response after
        virtual bool Execute() = 0;
    };
}

#endif //CPPLS2_CLIENT_ICOMMAND_H
