#ifndef CPPLS2_CLIENT_CLIENT_H
#define CPPLS2_CLIENT_CLIENT_H

#include <string>
#include <memory>
#include <asio.hpp>

class client
{
    const std::string hostname;
    const std::string port;
    const std::string base_directory;
    std::unique_ptr<asio::ip::tcp::iostream> server;

    const std::string prompt{ "avansync> " };
    const std::string lf{ "\n" };
    const std::string crlf{ "\r\n" };
public:
    client(const std::string& hostname, const std::string& port, const std::string& baseDirectory);

    void connect();
    void run();
};

#endif //CPPLS2_CLIENT_CLIENT_H
