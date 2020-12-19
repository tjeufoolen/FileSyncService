#ifndef CPPLS2_CLIENT_ICOMMAND_H
#define CPPLS2_CLIENT_ICOMMAND_H

namespace Commands {
    struct ICommand
    {
        virtual bool Execute() = 0;
        virtual void HandleResponse() = 0;
    };
}

#endif //CPPLS2_CLIENT_ICOMMAND_H
