#ifndef CPPLS2_SERVER_CLIENTDISCONNECTEXCEPTION_H
#define CPPLS2_SERVER_CLIENTDISCONNECTEXCEPTION_H

#include <exception>

namespace Exceptions {
    struct ClientDisconnectException : public std::exception
    {
        const char* what() const throw ()
        {
            return "The client disconnected.";
        }
    };
}

#endif //CPPLS2_SERVER_CLIENTDISCONNECTEXCEPTION_H
