#ifndef CPPLS2_SERVER_SERVER_H
#define CPPLS2_SERVER_SERVER_H

#include <string>
#include <memory>
#include <asio.hpp>

class Server
{
    const int PORT;

    asio::io_context io_context_;
    std::unique_ptr<asio::ip::tcp::acceptor> server_;
public:
    static const std::string BASE_DIRECTORY;
public:
    Server(int port);

    void Start();

    [[noreturn]] void Run();
    void HandleRequest(asio::ip::tcp::iostream& client, const std::vector<std::string>& args);
};

#endif //CPPLS2_SERVER_SERVER_H
