#ifndef CPPLS2_CLIENT_CLIENT_H
#define CPPLS2_CLIENT_CLIENT_H

#include <string>
#include <memory>
#include <asio.hpp>

class Client
{
    const std::string HOSTNAME;
    const std::string PORT;
    const std::string BASE_DIRECTORY;

    std::unique_ptr<asio::ip::tcp::iostream> server_;
public:
    Client(const std::string& hostname, const std::string& port, const std::string& baseDirectory);

    void connect();
    void run();

    void handleResponse(const std::string& response);
    void handleRequest(const std::string& request, const std::vector<std::string>& args);
};

#endif //CPPLS2_CLIENT_CLIENT_H
