#ifndef CPPLS2_SERVER_CLIENTDISCONNECTEXCEPTION_H
#define CPPLS2_SERVER_CLIENTDISCONNECTEXCEPTION_H

#include <exception>

namespace Exceptions {
    struct EndSessionException : public std::exception
    {
        const char* what() const throw ()
        {
            return "The session is ended.";
        }
    };
}

#endif //CPPLS2_SERVER_CLIENTDISCONNECTEXCEPTION_H
