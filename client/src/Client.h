#ifndef CPPLS2_CLIENT_CLIENT_H
#define CPPLS2_CLIENT_CLIENT_H

#include <string>
#include <memory>
#include <asio.hpp>

class Client
{
    const std::string HOSTNAME;
    const std::string PORT;

    std::unique_ptr<asio::ip::tcp::iostream> server_;
public:
    static const std::string BASE_DIRECTORY;
public:
    Client(const std::string& hostname, const std::string& port);

    void Connect();
    void Run();

    // boolean return type indicates if we should stop running or not.
    bool HandleCommand(const std::string& request, const std::vector<std::string>& args);
};

#endif //CPPLS2_CLIENT_CLIENT_H
