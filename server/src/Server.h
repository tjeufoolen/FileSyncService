#ifndef CPPLS2_SERVER_SERVER_H
#define CPPLS2_SERVER_SERVER_H

#include <string>
#include <memory>
#include <asio.hpp>

class Server
{
    const int PORT;
    const std::string BASE_DIRECTORY;

    asio::io_context io_context_;
    std::unique_ptr<asio::ip::tcp::acceptor> server_;
public:
    Server(int port, const std::string& baseDirectory);

    void start();
    void run();
    void handleRequest(asio::ip::tcp::iostream& client, const std::vector<std::string>& args);
};

#endif //CPPLS2_SERVER_SERVER_H
